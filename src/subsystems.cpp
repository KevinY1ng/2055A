#include "main.h"


//--------------------------------------------------------------------------------------------------
//Clamping Mobile Goal
// -------------------------------------------------------------------------------------------------

// bool clamp_status = true;

// void ClampTilt_Goal () {
//     if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
//         clamp_status = !clamp_status;
//         // clamp_status = true;
//         clamp.set_value(clamp_status);
//         pros::delay(250);
//         tilt.set_value(clamp_status);
//         // clamp.set_value(false);
//     }
// }

bool clampState = false;
void driveClamp()
{
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
        clampState = !clampState;
        clamp.set_value(clampState);
    }
}

// void setarm() {
//     if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
//     {
//         lbgetring(1, 5);
//     }
// }

bool raised = false;
int current_velocity = 0;
double armP = 0.05;
void setArmLoad()
{
	while (true)
	{
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) && !raised)
		{
			while(armsensor.get_position() < 13500)
			{
				arm.move_velocity(600);
				pros::delay(1);
			}
			arm.move_velocity(0);
			raised = true; 
		}
		else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) && raised)
		{
			while (armsensor.get_position() > 400)
			{
				arm.move_velocity(-600);
				pros::delay(1);
			}
			arm.move_velocity(0);
			raised = false;
		}
		else
		{
			// makeshift hold function (probably pretty bad)
			current_velocity = armsensor.get_velocity();
			if (current_velocity > 200 || current_velocity < 200)
			{
				arm.move_velocity(current_velocity * armP * -1);
			}
			pros::delay(1);
		}
	}
}
bool armraise = false;
void armtest() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            // if (armraise = false) {
                while (armsensor.get_angle() > 100) {
                    arm.move(120);
                    pros::delay(1);
                    armraise != armraise;
               }
            arm.brake();
            // if (armraise = true) {
            //     while (armsensor.get_angle() > 200) {
            //         arm.move(-120);
            //         pros::delay(1);
            //         armraise != armraise;
            //     }
            // }
            
    }
}
// }


bool checkForJam = false;
void setIntake(int power)
{
    intake1.move(power);
    intake2.move(power);
    // intake2.move(power);
}

// this function is used for turning on the intake when driving
void driveIntake() 
{
    int power = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)); // power = 127 if L1 is being pressed, otherwise power = 0
    intake1.move(power);
    intake2.move(power); // sets intake power to "power"
    // int power2 = 110 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
    // intake2.move(power2);
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
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        doink_status = !doink_status;
        doinker.set_value(doink_status);
    }
}

// double armkP =  0.05;
// int current_velocity_2;
// THIS FUNCTION IS FOR TESTING. HOLDING L1 RAISES THE ARM, HOLDING L2 LOWERS THE ARM UNTIL YOU LET GO.
void driveArm()
{
    int arm_power = 60 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
    if (armsensor.get_position() > 13000)
    {
        if (arm_power > 0)
        {
            arm_power = 0;
        }
    }
    if (armsensor.get_position() < 0)
    {
        if (arm_power < 0)
        {
            arm_power = 0;
        }
    }

    // if (arm_power == 0)
    // {
    //     current_velocity_2 = armsensor.get_velocity();
    //     if (current_velocity_2 > 200 || current_velocity_2 < 200)
    //     {
    //         arm.move_velocity(current_velocity_2 * armkP * -1);
    //     }
    // }
    // if (arm_power = 0)
    // {
        
    // }
    arm.move(arm_power);
}
    
bool clawState = false;
void driveClaw()
{
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X))
    {
        clawState = !clawState;
        claw.set_value(clawState);
    }
}