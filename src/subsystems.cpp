#include "main.h"


//--------------------------------------------------------------------------------------------------
//Clamping Mobile Goal
// -------------------------------------------------------------------------------------------------

bool clamp_status = false;

void Clamp_Goal () {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        clamp_status = !clamp_status;
        // clamp_status = true;
        clamp.set_value(clamp_status);
        // clamp.set_value(false);
    }
}

//-------------------------------------------------------------------------------------------------
//Clamp Tilt Angle
// ------------------------------------------------------------------------------------------------

bool tilt_status = false;

void Clamp_Tilt () {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        tilt_status = !tilt_status;
        tilt.set_value(tilt_status);
    }
}

bool checkForJam = false;
void setIntake(int power)
{
    intake1.move(power);
    intake2.move(power);
}

// this function is used for turning on the intake when driving
void driveIntake() 
{
    int power = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)); // power = 127 if L1 is being pressed, otherwise power = 0
    setIntake(power); // sets intake power to "power"
}

bool checkforJam()
{
    if (abs(intake1.get_actual_velocity()) > 10)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void fixJam()
{
    setIntake(0);
    pros::delay(250);
    setIntake(127);
}

void antiJamTask()
{
    while (true)
    {
        if (checkForJam)
        {
            if (abs(intake1.get_actual_velocity()) < 10)
            {
                setIntake(0);
                pros::lcd::set_text(2, "JAM DETECTED: MOTOR STOPPED.");
                pros::delay(250);
                setIntake(127);
                pros::lcd::set_text(3, "WAIT COMPLETED: MOTOR SPINNING.");
            }
        }
    pros::delay(100);
    }
}

bool doink_status = false;
void doink() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        doink_status = !doink_status;
        doinker.set_value(doink_status);
    }
}
    
  
