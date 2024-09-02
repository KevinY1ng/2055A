#include "main.h"


//--------------------------------------------------------------------------------------------------
//Clamping Mobile Goal
// -------------------------------------------------------------------------------------------------

bool clamp_status = false;

void Clamp_Goal() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        clamp_status =! clamp_status;
        clamp.set_value(clamp_status);
    }
}

//-------------------------------------------------------------------------------------------------
//Clamp Tilt Angle
// ------------------------------------------------------------------------------------------------

bool tilt_status = false;

void Clamp_Tilt () {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        tilt_status = !tilt_status;
        tilt.set_value(tilt_status);
    }
}

void setIntake(int power)
{
    intake.move(power);
}

// this function is used for turning on the intake when driving
void driveIntake() 
{
    int power = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)); // power = 127 if L1 is being pressed, otherwise power = 0
    setIntake(power); // sets intake power to "power"
}