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
        setDriveMotors(); // sets motors based on joystick inputs
        driveIntake(); // sets intake based on L1 input
        doink();
        ClampTilt_Goal();
    }
}