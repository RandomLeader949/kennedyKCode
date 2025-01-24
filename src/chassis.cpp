#include "chassis.hpp"
#include <cmath>

Chassis::Chassis(pros::Motor* lf, pros::Motor* lb, pros::Motor* rf, pros::Motor* rb, pros::IMU* imuSensor) 
    : leftFront(lf), leftBack(lb), rightFront(rf), rightBack(rb), imu(imuSensor) {}

void Chassis::setPower(double leftPower, double rightPower) {
    leftFront->move(leftPower);
    leftBack->move(leftPower);
    rightFront->move(rightPower);
    rightBack->move(rightPower);
}
void Chassis::drive(int speed, int distance) {
    leftFront->move(speed);
    rightFront->move(speed);
    rightBack->move(speed);
    leftBack->move(speed);
    pros::delay(distance);
    leftFront->brake();
    leftBack->brake();
    rightFront->brake();
    rightBack->brake();
}
void Chassis::turn(int speed, int degree){
    leftFront->move(speed);
    leftBack->move(speed);
    rightFront->move(-speed);
    rightBack->move(-speed);
    pros::delay(degree);
    leftFront->brake();
    leftBack->brake();
    rightFront->brake();
    rightBack->brake();
}
void Chassis::arcadeDrive(double forward, double turn) {
    turn *= -1;
    double leftPower = forward + turn;
    double rightPower = forward - turn;

    setPower(leftPower, rightPower);
}

void Chassis::tankDrive(double leftInput, double rightInput) {
    setPower(leftInput, rightInput);
}

void Chassis::resetIMU() {
    imu->reset();
    pros::delay(2000); // Wait for IMU calibration
}

double Chassis::getHeading() {
    return imu->get_heading();
}
