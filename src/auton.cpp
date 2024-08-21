#include "main.h"
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

void PID_Test() {
    chassis.setPose(0,0,0);
    turn(90,30,0.01,0,0);
}

void straightTest() {
    setDrive(8000, 8000);
    pros::delay(2000);
    setDrive(0, 0);
    pros::delay(2000);
}
    
