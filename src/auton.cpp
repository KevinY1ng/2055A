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
    // chassis.moveToPose(0,27,0,5000, {.maxSpeed=80, .minSpeed = 80, .earlyExitRange = 0.0000000001});
    chassis.moveToPose(0, 48, 0, 3500, {.earlyExitRange = 2});
    chassis.waitUntilDone();
    chassis.moveToPose(0, 24, 0, 3500, {.forwards = false, .earlyExitRange = 2});
    chassis.waitUntilDone();
    pros::delay(1000);
    chassis.moveToPose(0, 48, 0, 3500, {.earlyExitRange = 2});
    chassis.waitUntilDone();
    //chassis.turnToHeading(90, 5000);
    // chassis.moveToPose(0, 24, 0, 5000);
    // chassis.moveToPose(0, 0, -90, 5000);
    // pros::delay(1000);
    // chassis.moveToPose(0, 0, 0, 5000, {.forwards=false});
    // chassis.waitUntilDone();
    // pros::delay(1000);
    // chassis.moveToPose(0, 48, 0, 5000);
    // chassis.waitUntilDone();   
    // pros::delay(1000);
    // chassis.moveToPose(0, 0, 0, 5000, {.forwards=false});
    // chassis.waitUntilDone();

    // turn(90,50,0.021,0,0.092);
}

void straightTest() {
    setDrive(8000, 9500);
    pros::delay(2000);
    setDrive(0, 0);
    pros::delay(2000);
}

void PID_Turn() {
    // driveDistance(48,0.7,8,0,0);
    driveDistance(48, 0.7, 8, 0, 0, 1.95);
    //pros::delay(5000);
    //driveDistance(-24,20,0.2,0,0.6);
}   

void auton_test()
{
    chassis.setPose(0, 0, 0);
    chassis.moveToPose(0, 24, 0, 3000);
    chassis.turnToHeading(90, 1000);
    setIntake(127);
}

void mogo_rush()
{
    chassis.setPose(51,-36,90);
    chassis.moveToPoint(14, -36, 4000, {.forwards = false}, false);
    chassis.turnToHeading(60, 1000, {}, false);

    /* PATH PLAN
    51, -36, 90
    14, -36, 90
    14, -36, 60
    12, -38, 60
    12, -38, 135
    19, -42, 135
    19, -42, 190
    22, -35, 190
    22, -35, 36
    44, -4, 36
    44, -4, -78
    37, -2, -78
    */
}

    
//second option(starts from the right)
void mogo_rush()
{
    chassis.setPose(51,25,90);
    chassis.moveToPoint(34, 25, 4000, {.forwards = false}, false);
    chassis.turnToHeading(-24, 1000, {}, false);
}