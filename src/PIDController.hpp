#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

class PIDController {
public:
    // Constructor for PID controller
    PIDController(double kp, double ki, double kd);

    // Calculate the output of the PID loop
    double calculate(double target, double current, bool reset = false);

    // Reset the integral and previous error
    void reset();

private:
    double kP;       // Proportional gain
    double kI;       // Integral gain
    double kD;       // Derivative gain
    double integral; // Integral term
    double prevError;// Previous error
};

#endif
