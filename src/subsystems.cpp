#include "main.h"

//------------------------------------------------------------------------------------------------
//Clamping Mobile Goal
// ------------------------------------------------------------------------------------------------

bool clamp_status = 0;

void Clamp_Goal() {
    if (controller1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        clamp_status =! clamp_status;
        clamp.set_value(clamp_status);
    }
}

//------------------------------------------------------------------------------------------------
//Clamp Tilt Angle
// ------------------------------------------------------------------------------------------------

bool tilt_status = 0;

void Clamp_Tilt () {
    if (controller1.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
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