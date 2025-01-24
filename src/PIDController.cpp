#include "PIDController.hpp"

// Constructor to initialize the PID gains
PIDController::PIDController(double kp, double ki, double kd)
    : kP(kp), kI(ki), kD(kd), integral(0), prevError(0) {}

// Calculate the PID output
double PIDController::calculate(double target, double current, bool reset) {
    if (reset) {
        this->reset();
    }

    double error = target - current;
    integral += error;
    double derivative = error - prevError;

    double output = (kP * error) + (kI * integral) + (kD * derivative);

    prevError = error;

    return output;
}

// Reset the PID controller
void PIDController::reset() {
    integral = 0;
    prevError = 0;
}
