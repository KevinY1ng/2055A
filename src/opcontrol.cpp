 #include "main.h"
#include "api.h"
#include "pros/adi.hpp"
#include "pros/gps.h"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/vision.hpp"
#include "lemlib/api.hpp"

void my_opcontrol()
{
    // pros::rtos::Task my_task(my_task_fn);
    while (true)
    {
        
        //pros::lcd::set_text(1, std::to_string(colorsensor.get_hue()));
        // pros::lcd::set_text(3, std::to_string(colorsensor.get_hue()));
        // armsensor.reset_position();
        // setarm();
        setDriveMotors(); // sets motors based on joystick inputs
        driveIntake(); // sets intake based on L1 input -- comment this when running colorsort task
        driveClamp();
        // setArmLoad();
        driveClaw();
        doink();
        // ClampTilt_Goal();
        driveArm();
        armtest();
        // setarm();
        pros::lcd::set_text(1, std::to_string(armsensor.get_position()));
        pros::delay(1);
    }
}

