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

void turn(double targetheading, double maxspeed, float kP, float kI, float kD) {
    double currentheadibng = imu.get_rotation();
    double error = targetheading - currentheadibng;
    double errortotal = 0;
    float lasterror;
    double dT = 50;

    while (abs(error)>2) {
        double currentheading = imu.get_rotation();
        double error = targetheading - currentheading;

        if (error < 5 || error !=0) {
            errortotal += error;
        }
        else {
            errortotal = 0;
        }

        if (errortotal > 50 / kI) {
            errortotal = 50 / kI;
        }

        double proportional = kP * error;
        double integral = kI * errortotal;
        double derivative = (error - lasterror) / dT * kD;

        double preverror = error;

        double output = proportional + integral + derivative;

        drive_LF.move(output * maxspeed);
        drive_LM.move(output * maxspeed);
        drive_LB.move(output * maxspeed);

        drive_RF.move(output * -maxspeed);
        drive_RM.move(output * -maxspeed);
        drive_RB.move(output * -maxspeed);

        lasterror = error;

        pros::delay(20);
    }
      drive_LF.move(0);
        drive_LM.move(0);
        drive_LB.move(0);

        drive_RF.move(0);
        drive_RM.move(0);
        drive_RB.move(0);
}