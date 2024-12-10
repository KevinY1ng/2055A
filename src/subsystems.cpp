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

// ideal position: 1064

int currentAngle;
int error = 1064;
const double kP = 0.035;
const int deadband = 150;
const int targetAngle = 730;
bool hold;
void setArmLoadNew()
{
    while (true)
    {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
        {
            arm.set_brake_mode(MOTOR_BRAKE_HOLD);
            currentAngle = armsensor.get_angle();
            if (30000 <= currentAngle && currentAngle <= 36000) 
            {
                currentAngle = 0 - (36000 - currentAngle);
            }
            error = targetAngle - currentAngle;
            while (abs(error) > deadband)
            {
                currentAngle = armsensor.get_angle();
                if (30000 <= currentAngle && currentAngle <= 36000) 
                {
                    currentAngle = 0 - (36000 - currentAngle);
                }
                error = targetAngle - currentAngle;
                arm.move_velocity(error * kP);
                pros::lcd::set_text(3, "Speed: " + std::to_string(error * kP));
                pros::lcd::set_text(4, "Current Angle: " + std::to_string(currentAngle));
                pros::lcd::set_text(5, "Error: " + std::to_string(error));
                pros::delay(1);
            }
            arm.move_velocity(0);
            // arm.set_brake_mode(MOTOR_BRAKE_HOLD);
            // arm.move_velocity(0);
        }
        else
        {
            // hold arm in place if in loading position
            // if (hold)
            // {
            //     // 100 too fast, 40 too fast, 20 too fast, 10 too fast, 5 too fast, 2 too fast
            //     // this is the velocity at which the arm will move upwards to hold
            //     arm.move_velocity(0);
            // }
            driveArm();
            pros::delay(1);
        }
    }
}

bool armraise = false;
// void armtest() {
//     if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
//             // if (armraise = false) {
//                 while (armsensor.get_angle() > 100) {
//                     arm.move(120);
//                     pros::delay(1);
//                     armraise != armraise;
//                }
//             arm.brake();
//             // if (armraise = true) {
//             //     while (armsensor.get_angle() > 200) {
//             //         arm.move(-120);
//             //         pros::delay(1);
//             //         armraise != armraise;
//             //     }
//             // }
            
//     }
// }
// // }
//             if (armraise = false) {
//                 while (armsensor.get_angle() < 4500) {
//                     arm.move(120);
//                     pros::delay(1);
//                     armraise != armraise;
//                 }
//             if (armraise = true) {
//                 while (armsensor.get_angle() > 200) {
//                     arm.move(-120);
//                     pros::delay(1);
//                     armraise != armraise;
//                 }
//             }
            
//     }
// }
// }


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
    setIntake(power);
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

// HOLDING L1 RAISES THE ARM, HOLDING L2 LOWERS THE ARM UNTIL YOU LET GO.
void driveArm()
{
    int arm_power = 400 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
    arm.move_velocity(arm_power);
    // if the arm isn't holding, or if the driver clicks L1 or L2, the arm will move. Otherwise, if the driver does not click L1/L2 and the arm is holding, the arm will not move.
    // if (arm_power != 0 || (arm_power == 0 && hold == false))
    // {
    //     hold = false;
    //     arm.move(arm_power);
    // }
    // if (armsensor.get_position() > 13000)
    // {
    //     if (arm_power > 0)
    //     {
    //         arm_power = 0;
    //     }
    // }
    // if (armsensor.get_position() < 0)
    // {
    //     if (arm_power < 0)
    //     {
    //         arm_power = 0;
    //     }
    // }

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