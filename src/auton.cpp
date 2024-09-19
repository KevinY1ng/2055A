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
    setIntake(127);
    pros::delay(5000);
    setIntake(0);
}

/*
how to clamp
A - high
C - high
Go up to mobile goal
C - low
A - low

how to let go 
C - high

*/

/*
when you first start the code:
open the clamp
close the clamp
then tilt
and you've got the mobile goal
*/

void mogo_rush()
{
    /* NEW ROUTE */
    chassis.setPose(51, -23, 90);
    chassis.moveToPoint(25, -23, 2000, {.forwards=false, .maxSpeed=65}, false);
    clamp.set_value(false);
    tilt.set_value(false);
    setIntake(127);
    pros::delay(500);
    chassis.turnToHeading(183, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 60}, false);
    chassis.moveToPoint(25, -43, 3000, {}, false);
    pros::delay(5000);
    setIntake(0);




    /*
    chassis.setPose(51,-36,90);
    chassis.moveToPoint(14, -36, 2000, {.forwards = false, .maxSpeed = 85});
    clamp.set_value(true);
    chassis.waitUntilDone();
    chassis.turnToHeading(50, 1000, {.maxSpeed = 85}, false);
     // Move to (7, -43), unclamp, tilt
    chassis.moveToPoint(7, -43, 2000, {.forwards = false, .maxSpeed = 60}, false);
    clamp.set_value(false);
    pros::delay(500);
    tilt.set_value(false);
    pros::delay(500);
      // Turn and move to new point
    chassis.turnToHeading(105, 1000, {.direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 85}, false);
    chassis.moveToPoint(23, -46, 2000, {.maxSpeed=60});
    setIntake(127);
    chassis.waitUntilDone();
    pros::delay(1000);
    setIntake(0);
     // Clamp and move back
    tilt.set_value(true);
    clamp.set_value(true);
    pros::delay(250);
    chassis.turnToHeading(185, 1000, {}, false);
    chassis.moveToPoint(23, -24, 2000, {.forwards=false, .maxSpeed = 60}, false);
    clamp.set_value(false);
    pros::delay(500);
    tilt.set_value(false);
    pros::delay(500);
    */
    /*
    // Move to (12, -36, 90)
    chassis.moveToPoint(12, -36, 2000, {.forwards = true, .maxSpeed = 85});
    chassis.waitUntilDone();

     // Move to (12, -38, 60)
    chassis.moveToPoint(12, -38, 2000, {.forwards = true, .maxSpeed = 85});
    chassis.turnToHeading(60, 1000, {.maxSpeed = 85}, false);

      // Move to (19, -42, 135)
    chassis.moveToPoint(19, -42, 2000, {.forwards = true, .maxSpeed = 85});
    chassis.turnToHeading(135, 1000, {.maxSpeed = 85}, false);
    
    // Move to (22, -35, 190)
    chassis.moveToPoint(22, -35, 2000, {.forwards = true, .maxSpeed = 85});
    chassis.turnToHeading(190, 1000, {.maxSpeed = 85}, false);

    // following the path
    chassis.moveToPoint(44, -4, 2000, {.forwards = true, .maxSpeed = 85});
    chassis.turnToHeading(36, 1000, {.maxSpeed = 85}, false);
    
    // movement to (37, -2, -78)
    chassis.moveToPoint(37, -2, 2000, {.forwards = true, .maxSpeed = 85});
    chassis.turnToHeading(-78, 1000, {.maxSpeed = 85}, false);

    // Clamp release and end
    clamp.set_value(false);
    */

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
    clamp.set_value(true);
    chassis.setPose(53,24,90);
    chassis.moveToPoint(24, 24, 2000, {.forwards = false,.maxSpeed=60}, false);
    clamp.set_value(false);
    pros::delay(500);
    tilt.set_value(false);
    pros::delay(500);
    chassis.turnToHeading(0, 1000, {}, false);
    setIntake(127);
    chassis.moveToPoint(24, 46, 2000, {.forwards = true}, false);
    chassis.turnToHeading(-90, 1000, {}, false);
    chassis.moveToPoint(8, 46, 3000, {.forwards = true,.maxSpeed=60}, false);
    setIntake(0);
    chassis.moveToPoint(13, 46, 1000, {.forwards = false}, false);
    chassis.turnToHeading(0, 500, {}, false);
    chassis.moveToPoint(13, 22, 2000, {.forwards = false}, false);

   //chassis.moveToPose(, 24, 90, 5000, {}, false); setIntake(-127);
}

 /* PATH PLAN
    53,24,90 (start position)
    
    24,24,90(grab Mobile Goal)
    24,24,0(turn to face the ring)
    24,46,0(suck the ring)
    24,46,-90(face the rings)
    8,46,-90(suck two ring that in the front)
    12,46,-0(turn to face the ladder)
    12,23,0(reach ladder)
    */

void elim5ring() {
// //Get Mobile Goal
    chassis.setPose(-47,36,295);
    chassis.moveToPose(-24,26,295,2000,{.forwards = false, .maxSpeed = 65}, false);
    clamp.set_value(false);
    pros::delay(10);
    tilt.set_value(false);

//  //Get 2nd Ring
    chassis.turnToHeading(0,2000,{}, true);
    setIntake(115);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24,48,3000,{.maxSpeed = 90});

//  //Get 3rd and 4th Ring
    chassis.turnToHeading(65,1000,{}, false);
    setIntake(111);
    chassis.moveToPose(-8,51,65,2000,{.maxSpeed = 85});
    pros::delay(100);
    chassis.moveToPoint(-19,46,2000,{.forwards = false});
    pros::delay(100);
    chassis.turnToHeading(98,1000);
    chassis.moveToPoint(-10,45,2000, {.maxSpeed = 95});
//     pros::delay(100);
//     intake.brake();

//     //Get 5th Ring
    chassis.moveToPose(-46,31,61,1000,{.forwards = false, .maxSpeed = 110});
//     pros::delay(100);
//     chassis.turnToHeading(180,1000);
//     pros::delay(100);
//     chassis.moveToPoint(-46,12,180,3000);
}

void progskills() {

    //TIMEOUTS TEMPORARY

    //set pose
    chassis.setPose(-56.5, 2, 90);
    //alliance stake
    setIntake(-127);
    pros::delay(1500);
    setIntake(0);
    //collect ring
    chassis.moveToPoint(-24, -24, 2500, {.maxSpeed = 60});
    setIntake(127);
    chassis.waitUntilDone();
    pros::delay(500);
    setIntake(0);
    //get mogo
    chassis.turnToHeading(90, 750);
    tilt.set_value(true);
    clamp.set_value(true);
    chassis.waitUntilDone();
    chassis.moveToPose(-51,-24, 90, 1000,{.forwards = false}, false);
    clamp.set_value(false);
    pros::delay(500);
    tilt.set_value(false);
    pros::delay(500);
    //get ring
    setIntake(127);
    chassis.moveToPoint(-24, -48, 1000);
    chassis.waitUntil(10);
    chassis.cancelMotion();
    chassis.moveToPoint(-24, -48, 500, {.maxSpeed = 60}, false);
    pros::delay(500);
    //get ring
    chassis.turnToHeading(180, 750, {}, false);
    chassis.moveToPoint(-55, -48, 1500, {.maxSpeed=60}, false);
    pros::delay(500);
    chassis.turnToPoint(-48, -60, 750, {}, false);
    chassis.moveToPoint(-48, -60, 750, {.maxSpeed = 60, .minSpeed = 10}, false);
    chassis.turnToHeading(90, 500, {.minSpeed = 10});
    chassis.moveToPoint(0, -60, 1500, {}, false);
    pros::delay(500);
    chassis.moveToPoint(-48, -48, 1500, {.forwards=false}, false);
    chassis.turnToHeading(45, 750, {}, false);
    chassis.moveToPose(-60, -60, 45, 750, {.forwards = false}, false);
    tilt.set_value(true);
    clamp.set_value(true);
    setIntake(0);
    pros::delay(500);
    chassis.turnToPoint(-39, 0, 500, {}, false);
    chassis.moveToPoint(-39, 0, 3000, {.minSpeed=60}, false);
    chassis.moveToPoint(-24, 24, 1000, {.maxSpeed=60}, false);

}

void progskills2()  {
    //set pose
   chassis.setPose(-65, -55, 90);
   
   chassis.turnToHeading(0, 1000);
chassis.moveToPoint(-60, -45, 1000);
chassis.turnToHeading(40, 1000);
chassis.moveToPoint(-47, -34, 1000);
chassis.turnToHeading(0, 1000);

chassis.moveToPose(-25, 25, 90, 1000);
chassis.turnToHeading(200, 1000);

chassis.moveToPoint(-47, 15, 1000);
chassis.turnToHeading(180, 1000);
//clamp goal
clamp.set_value(true);
tilt.set_value(true);
chassis.waitUntilDone();

chassis.moveToPoint(-47, 40, 1000);
//pick up ring
setIntake(127);
chassis.waitUntil(10);
    chassis.cancelMotion();

chassis.moveToPoint(-47, 52, 1000);

//pick up ring
setIntake(127);
chassis.waitUntil(10);
    chassis.cancelMotion();

chassis.turnToHeading(230, 1000);
chassis.moveToPoint(-54, 54, 1000);
//pick up ring
setIntake(127);
chassis.waitUntil(10);
    chassis.cancelMotion();

chassis.moveToPose(-54, 49, 90,1000);

//put down goal
chassis.moveToPoint(-31, 48, 1000);
chassis.turnToHeading(90, 1000);
chassis.moveToPose(-61, 62, 120, 1000);
chassis.turnToHeading(120, 1000);
clamp.set_value(false);
tilt.set_value(false);

chassis.moveToPose(-60, 60, 90, 1000);
chassis.moveToPoint(-8, 60, 1000);
//pick up ring
setIntake(127);
chassis.waitUntil(10);
    chassis.cancelMotion();

chassis.moveToPose(19, 55, 140, 1000);
//pick up ring
setIntake(127);
chassis.waitUntil(10);
    chassis.cancelMotion();
    
}

void soloawp() {
//Score Alliance Ring
chassis.setPose(-58,-8,180);
chassis.moveToPoint(-58,0,1000,{.forwards = false, .maxSpeed = 30});
pros::delay(1000);
chassis.turnToHeading(90,2000, {.maxSpeed = 45});
pros::delay(2000);
intake2.move(-127);
pros::delay(700);
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
