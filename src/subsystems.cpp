#include "main.h"

// void Turn(double targetheading, double maxspeed) {

//     double heading = imu.get_rotation();
//     double error = targetheading - heading;

//     double integral = 0;
// 	double prevError = error;
// 	double dt = 50;

//     while (abs(error)>5) {

//         double heading = imu.get_rotation();
//         double error = targetheading - heading;

//         double proportional = error * kP;

// 		integral += error;
// 		double integ = integral * kI;

// 		double direvative = (error - prevError) / dt * kD;
// 		prevError = error;

// 		double output = proportional + integ + direvative;

// 		output = std::clamp(output, -1.0, 1.0);

// 		leftFront.move(maxSpeed * output);
// 		leftBack.move(maxSpeed * output);
// 		rightFront.move(-maxSpeed * output);
// 		rightBack.move(-maxSpeed * output);

// 		pros::delay(dt);

//     }

//     leftFront.move(0);
// 	leftBack.move(0);
// 	rightFront.move(0);
// 	rightBack.move(0);

// }


//------------------------------------------------------------------------------------------------
//Clamping Mobile Goal
// ------------------------------------------------------------------------------------------------

bool clamp_status = false;

void Clamp_Goal() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        clamp_status =! clamp_status;
        clamp.set_value(clamp_status);
    }
}

//------------------------------------------------------------------------------------------------
//Clamp Tilt Angle
// ------------------------------------------------------------------------------------------------

bool tilt_status = false;

void Clamp_Tilt () {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        tilt_status =! tilt_status;
        tilt.set_value(tilt_status);
    }
}