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
    chassis.moveToPoint(7, -43, 2000, {.forwards = false, .maxSpeed = 85}, false);
    clamp.set_value(false);
    tilt.set_value(false);
    pros::delay(500);
    chassis.turnToHeading(105, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 85}, false);
    chassis.moveToPoint(23, -46, 2000, {.maxSpeed=65});
    setIntake(127);
    chassis.waitUntilDone();
    pros::delay(500);
    setIntake(0);
    tilt.set_value(true);
    clamp.set_value(true);
    pros::delay(250);
    chassis.turnToHeading(185, 1000, {.maxSpeed=65}, false);
    chassis.moveToPoint(23, -30, 2000, {.forwards=false, .maxSpeed=85}, false);
    clamp.set_value(false);
    tilt.set_value(false);
    

    

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
    chassis.setPose(60,0,-90);
    setIntake(-127);
    chassis.moveToPoint(51, 0, 4000, {.forwards = false}, false);
    chassis.turnToHeading(132, 1000, {}, false);
    chassis.moveToPose(24, 24, 90, 5000, {}, false);
}

 /* PATH PLAN
    60,0,-90 (start position), scored in Assistance Wall Stick
    51,0,-90(suck the ring, but don't send them to the hood)
    51,0,132(turn to face Mobile Goal)
    31,17,132(grab Mobile Goal)
    31,17,-15(turn to face the ring)
    25,46,-15(suck the ring)
    10,46,-90(suck two ring that in the front)
    10,46,-180(turn to face the ladder)
    10,26,-180(reach ladder)
    */

void elim5ring() {
// //Get Mobile Goal
//     chassis.setpose(-47,36,295);
//     clamp.set_value(true);
//     chassis.moveToPose(-24,26,295,2000,{.maxspeed = 85});
//     clamp.set_value(false);
//     tilt.set_value(false);
//     chassis.waitUntilDone();

//     //Get 2nd Ring
//     chassis.turnToHeading(0,2000);
//     setIntake(115);
//     pros::delay(100);
//     chassis.moveToPoint(-24,45,0,3000,{.maxspeed = 90}, false);
//     pros::delay(100);
//     intake.brake();

//     //Get 3rd and 4th Ring
//     chassis.turnToHeading(90,1000);
//     setIntake(111);
//     chassis.moveToPoint(-14,45,90,2000,{.maxspeed = 85}, false);
//     pros::delay(200);
//     chassis.moveToPoint(-17,45,90,2000,(.forwards = false),false)
//     pros::delay(100);
//     chassis.turnToHeading(45,1000);
//     pros::delay(50);
//     chassis.moveToPoint(-12,48,61,2000);
//     pros::delay(100);
//     intake.brake();

//     //Get 5th Ring
//     chassis.moveToPose(-46,31,61,1000,{.forwards = false, .maxspeed = 110});
//     pros::delay(100);
//     chassis.turnToHeading(180,1000);
//     pros::delay(100);
//     chassis.moveToPoint(-46,12,180,3000);
}

void progskills() {

    //TIMEOUTS TEMPORARY

    //set pose
    chassis.setPose(-56.5, 0, 90);
    //alliance stake
    setIntake(-127);
    pros::delay(1500);
    setIntake(0);
    //collect ring
    chassis.moveToPoint(-24, -24, 2000);
    chassis.waitUntil(10);
    setIntake(127);
    chassis.waitUntilDone();
    pros::delay(500);
    //get mogo
    chassis.turnToHeading(90, 1000);
    tilt.set_value(false);
    clamp.set_value(false);
    chassis.waitUntilDone();
    chassis.moveToPoint(-51,-24,1000,{}, false);
    clamp.set_value(true);
    tilt.set_value(true);
    pros::delay(500);
    //get ring
    chassis.moveToPoint(-24, -48, 100, {}, false);
    pros::delay(500);
    chassis.turnToHeading(180, 1000, {}, false);
    chassis.moveToPoint(-43, -48, 750, {}, false);
    

}

void soloawp() {
//Score Alliance Ring
chassis.setPose(-58,-8,180);
chassis.moveToPoint(-58,0,1000,{.forwards = false, .maxSpeed = 30});
chassis.turnToHeading(90,500, {.maxSpeed = 50});
intake2.move(-127);
pros::delay(300);
intake2.brake();
pros::delay(1000);

//Get 2nd Ring
// setIntake(127);
// chassis.moveToPose(-43,0,90,2000);

// //Get Mobile Goal
// chassis.turnToHeading(215,300, {.maxSpeed = 85});
// chassis.moveToPoint(-26,26,2000, {.forwards = false, .maxSpeed = 105});

// //Get 3rd and 4th Ring
// chassis.turnToHeading(5,500, {.direction = AngularDirection::CW_CLOCKWISE});
// setIntake(127);
// chassis.moveToPoint(23,54,1000,{.maxSpeed = 90});
// chassis.turnToHeading(90,500);
// intake1.brake();
// intake2.brake();
// chassis.moveToPoint(-14,54,1000);
// intake1.move(127);
}
