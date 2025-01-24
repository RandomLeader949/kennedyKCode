#ifndef CHASSIS_HPP
#define CHASSIS_HPP

#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"

class Chassis {
private:
    pros::Motor* leftFront;
    pros::Motor* leftBack;
    pros::Motor* rightFront;
    pros::Motor* rightBack;
    pros::IMU* imu;

public:
    Chassis(pros::Motor* lf, pros::Motor* lb, pros::Motor* rf, pros::Motor* rb, pros::IMU* imuSensor);

    void setPower(double leftPower, double rightPower);
    void arcadeDrive(double forward, double turn);
    void tankDrive(double leftInput, double rightInput);
    void resetIMU();
    void drive(int speed, int distance);
    void turn(int speed, int degree);
    double getHeading();
};

#endif
