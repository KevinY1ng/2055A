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