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
    chassis.moveToPoint(14, -36, 2000, {.forwards = false, .maxSpeed = 85});
    clamp.set_value(true);
    chassis.waitUntilDone();
    chassis.turnToHeading(50, 1000, {.maxSpeed = 85}, false);
    chassis.moveToPoint(9, -41, 2000, {.forwards = false, .maxSpeed = 85}, false);
    clamp.set_value(false);
    tilt.set_value(false);
    pros::delay(500);
    chassis.turnToHeading(115, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 85}, false);
    setIntake(-110);
    

    /* PATH PLAN
    51, -36, 90
    12, -36, 90
    12, -36, 60
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
void mogo_rushright()
{
    chassis.setPose(51,25,90);
    chassis.moveToPoint(34, 25, 4000, {.forwards = false}, false);
    chassis.turnToHeading(-24, 1000, {}, false);
}

// void elim5ring() {
// //Get Mobile Goal
//     chassis.setpose(-47,36,295);
//     clamp.set_value(true);
//     chassis.moveToPose(-24,26,295,2000);
//     clamp.set_value(false);
//     tilt.set_value(false);
//     chassis.waitUntilDone();
//     setIntake(115);
//     pros::delay(300);

//     //Get 2nd Ring
//     intake.brake();
//     chassis.turnToHeading(0,2000);
//     pros::delay(100);
//     setIntake(115);
//     chassis.moveToPoint(-24,45,0,3000,{.maxspeed = 80}, false);
//     pros::delay(500);
//     intake.brake();

//     //Get 3rd and 4th Ring
//     chassis.turnToHeading(90,1000);
//     setIntake(111);
//     chassis.moveToPoint(-14,45,90,2000,true);
//     pros::delay(500);
//     chassis.moveToPoint(-17,45,90,2000,(.forwards = false),false)
//     pros::delay(500);
//     chassis.turnToHeading(45,1000);
//     pros::delay(50);
//     chassis.moveToPoint(-12,48,61,2000);
//     pros::delay(500);
//     intake.brake();

//     //Get 5th Ring
//     chassis.moveToPose(-46,31,61,1000,{.forwards = false, .maxspeed = 110});
//     pros::delay(100);
//     chassis.turnToHeading(180,1000);
//     pros::delay(100);
//     chassis.moveToPoint(-46,12,180,3000);
// }

void progskills() {
// First Corners Rings
// -61,-21,270
// -47,-21,270
// -47,-21,90
// -23,-21,90
// -23,-21,180
// -24,-45,180
// -24,-45,270
// -51,-45,270
// -51,-45,170
// -50,-48,170
// -50,-48,45
// -57,-54,45


}