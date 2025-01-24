#include "main.h"
#include "liblvgl/lvgl.h"
#include "pblogo.h"
#include "fordLogo.h"
#include "chassis.hpp"
pros::Motor leftFrontMotor(20);
pros::Motor leftBackMotor(19);
pros::Motor rightFrontMotor(-18);
pros::Motor rightBackMotor(-17);
pros::IMU inertialSensor(21);

pros::MotorGroup arm({-1, 2});
pros::Motor intakeStage1(5);
pros::Motor intakeStage2(-6);
pros::Motor lock(5);
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::ADIDigitalOut claw('H'); // Pneumatic connected to port A
Chassis chassis(&leftFrontMotor, &leftBackMotor, &rightFrontMotor, &rightBackMotor, &inertialSensor);

lv_obj_t *img;
int intakeRPM = 128;
bool dualLock = true;
void loadPB()
{
	// Load the image
	LV_IMG_DECLARE(pblogo);					  // Ensure this is declared correctly in your project
	img = lv_img_create(lv_scr_act());		  // Correctly create the image without NULL
	lv_img_set_src(img, &pblogo);			  // Set the image source
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0); // Center the image on the screen
}
void loadFord()
{
	// Load the image
	LV_IMG_DECLARE(fordLogo);				  // Ensure this is declared correctly in your project
	img = lv_img_create(lv_scr_act());		  // Correctly create the image without NULL
	lv_img_set_src(img, &fordLogo);			  // Set the image source
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0); // Center the image on the screen
}
void autonomous()
{
	chassis.drive(127, 1);
	chassis.turn(60, 90);
}
void wallMode()
{
	intakeRPM = 128 / 2;
}
void moboMode()
{
	intakeRPM = 128;
}
void opcontrol()
{
	claw.set_value(false);
	arm.set_brake_mode(MOTOR_BRAKE_HOLD);
	while (true)
	{
		double left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);	 // Forward/backward
		double right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // Turning
		chassis.arcadeDrive(left, right);
		arm.brake();
		intakeStage1.brake();
		intakeStage2.brake();
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
			dualLock = false;
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			dualLock = true;
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			moboMode();
			master.clear();
			master.print(0, 0, "mobo");
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			wallMode();
			master.clear();
			master.print(0, 0, "wall");
		}
		if (dualLock)
		{
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
			{
				intakeStage1.move(intakeRPM);
				intakeStage2.move(intakeRPM);
				pros::delay(10);
			}
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
			{
				intakeStage1.move(-intakeRPM);
				intakeStage2.move(-intakeRPM);
				pros::delay(10);
			}
		}
		if (!dualLock)
		{
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
			{
				intakeStage2.move(-intakeRPM);
								pros::delay(10);

			}
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
			{
				intakeStage2.move(intakeRPM);
								pros::delay(10);

			}
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
			{
				intakeStage1.move(intakeRPM);
								pros::delay(10);

			}
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
			{
				intakeStage1.move(-intakeRPM);
								pros::delay(10);

			}
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			lock.move(-60);
			pros::delay(10);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			lock.move(60);
			pros::delay(10);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			arm.move(127 / 2);
			pros::delay(10);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			arm.move(-127 / 2);
			pros::delay(10);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
		{
			claw.set_value(false);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
		{
			claw.set_value(true);
		}
	}
}
