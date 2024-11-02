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

void sortRed(int power,int timeout) {
    double startTime = pros::millis();
    while ((pros::millis() - startTime) < timeout) {
        double colorvalue = colorsensor.get_hue();
        if (colorvalue >= 7 && colorvalue <= 19)
            {
                pros::lcd::set_text(4, "RED RING DETECTED! :(");
                // pros::delay(5);
                intake1.move(127);
                intake2.move(-127);
                pros::delay(600);
                //setIntake(0);
            }
        else {
            setIntake(power);
        }
    }
    setIntake(0);
}


void straightTest() {
    setDrive(8000, 9500);
    pros::delay(2000);
    setDrive(0, 0);
    pros::delay(2000);
}

void auton_test()
{
    chassis.setPose(-47, -54, 180);
   chassis.moveToPoint(-47, 13, 3500, {.forwards=false, .maxSpeed=80}, false);
    // chassis.moveToPoint(-47, 19, 1250, {.forwards=false, .maxSpeed=60}, false);
    chassis.moveToPoint(-47, 27, 1500, {.forwards=false}, false);
    pros::delay(250);
    clamp.set_value(false);
    pros::delay(500);
    tilt.set_value(false);
    pros::delay(250);
       
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

// don't use this for Highlander
void mogo_rush()
{
    /* NEW ROUTE */
    chassis.setPose(51, -23, 90);
    chassis.moveToPoint(25, -23, 2000, {.forwards=false, .maxSpeed=65}, false);
    //coordx/y, timeout in ms (if robot hasnt met target position, quits) {specifications .forwards means go backwards} asynchronous, if true it will run the next line simultaneously;
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
// don't use this for highlander
void mogo_rushright()
{
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.setPose(53,24,90);
    chassis.moveToPoint(24, 24, 2000, {.forwards = false,.maxSpeed=55}, false);
    clamp.set_value(false);
    pros::delay(500);
    tilt.set_value(false);
    pros::delay(500);
    chassis.turnToHeading(0, 1000, {}, false);
    setIntake(95);
    chassis.moveToPoint(24, 46, 2000, {.forwards = true}, false);
    chassis.turnToHeading(-90, 1000, {}, false);
    chassis.moveToPoint(8, 46, 3000, {.forwards = true,.maxSpeed=60}, false);
    chassis.moveToPoint(13, 46, 1000, {.forwards = false}, false);
    chassis.turnToHeading(0, 500, {}, false);
    setIntake(0);
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

void elim5ringRed() {
// //Get Mobile Goal
    chassis.setPose(-47,36,295);
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.moveToPose(-24,26,295,2000,{.forwards = false, .maxSpeed = 65}, false);
    clamp.set_value(false);
    pros::delay(10);
    tilt.set_value(false);

//  //Get 2nd Ring
    setIntake(115);
    chassis.moveToPose(-24,46,0,2000,{.maxSpeed = 105},true);

//  //Get 3rd and 4th Ring
    chassis.turnToHeading(90,1000,{}, true);
    setIntake(111);
    chassis.moveToPose(-10,52,90,1500,{.maxSpeed = 127},true);
    chassis.moveToPoint(-16,52,1500,{.forwards = false},true);
    // chassis.turnToHeading(120,1000,{},true);
    chassis.moveToPose(-10,45,120,2000, {.maxSpeed = 125},true);
//     pros::delay(100);
//     intake.brake();

//     //Get 5th Ring
    chassis.moveToPose(-47,19,61,3000,{.forwards = false, .minSpeed = 127},true);
//     pros::delay(100);
    chassis.turnToHeading(180,1000);
//     pros::delay(100);
    // clamp.set_value(false);    
    // chassis.turnToHeading(137, 1000, {}, false);
    // chassis.moveToPoint(-29, 5, 2500, {.maxSpeed = 50}, false);
}

void elim5ringBlue()
{
    // //Get Mobile Goal
    chassis.setPose(47,36,55);
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.moveToPose(24,26,55,2000,{.forwards = false, .maxSpeed = 65}, false);
    clamp.set_value(false);
    pros::delay(10);
    tilt.set_value(false);

//  //Get 2nd Ring
    setIntake(115);
    chassis.moveToPose(24,49,0,2000,{.maxSpeed = 105},true);

//  //Get 3rd and 4th Ring
    chassis.turnToHeading(-90,1000,{}, true);
    setIntake(111);
    chassis.moveToPose(10,52,-90,1500,{.maxSpeed = 125},true);
    chassis.moveToPoint(16,52,1500,{.forwards = false},true);
    // chassis.turnToHeading(120,1000,{},true);
    chassis.moveToPose(10,45,-120,2000, {.maxSpeed = 125},true);
//     pros::delay(100);
//     intake.brake();

//     //Get 5th Ring
    chassis.moveToPose(47,19,-61,3000,{.forwards = false, .minSpeed = 127},true);
//     pros::delay(100);
    chassis.turnToHeading(180,1000);
//     pros::delay(100);
    // clamp.set_value(false);    
    // chassis.turnToHeading(-137, 1000, {}, false);
    // chassis.moveToPoint(29, 5, 2500, {.maxSpeed=50}, false);
}

void qual5ringRed()
{
    // //Get Mobile Goal
    chassis.setPose(-47,36,295);
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.moveToPose(-24,26,295,2000,{.forwards = false, .maxSpeed = 65}, false);
    clamp.set_value(false);
    pros::delay(10);
    tilt.set_value(false);

//  //Get 2nd Ring
    setIntake(115);
    chassis.moveToPose(-24,46,0,2000,{.maxSpeed = 105},true);

//  //Get 3rd and 4th Ring
    chassis.turnToHeading(90,1000,{}, true);
    setIntake(111);
    chassis.moveToPose(-10,52,90,1500,{.maxSpeed = 127},true);
    chassis.moveToPoint(-16,52,1500,{.forwards = false},true);
    // chassis.turnToHeading(120,1000,{},true);
    chassis.moveToPose(-10,45,120,2000, {.maxSpeed = 125},true);
//     pros::delay(100);
//     intake.brake();

//     //Get 5th Ring
    chassis.moveToPose(-47,19,61,3000,{.forwards = false, .minSpeed = 127},true);
//     pros::delay(100);
    chassis.turnToHeading(180,1000);
//     pros::delay(100);
    clamp.set_value(false);    
    chassis.turnToHeading(137, 1000, {}, false);
    chassis.moveToPoint(-29, 5, 2500, {.maxSpeed = 50}, false);
}

void qual5ringBlue()
{   
    chassis.setPose(51, 24, 90);
    clamp.set_value(true);
    tilt.set_value(true);

//Get Mobile Goal
    chassis.moveToPoint(24, 24, 2500, {.forwards=false, .maxSpeed=65}, true);
    chassis.waitUntil(20);
    clamp.set_value(false);
    pros::delay(50);
    tilt.set_value(false);
    chassis.waitUntilDone();

//Get 2nd Ring
    pros::delay(200);
    setIntake(127); 
    pros::delay(100);
    chassis.turnToHeading(0, 500, {.maxSpeed=65}, false);

//Get 3rd Ring
    chassis.moveToPoint(24, 53, 1500, {.maxSpeed=75}, false);
    pros::delay(300);
    chassis.turnToHeading(-90, 800, {.maxSpeed=65}, false);
    chassis.moveToPoint(9, 53, 1500, {.maxspeed=95}, false);
    pros::delay(200);
    //9,53,-155
    //6,47,-155
    //6,47,-90
    //13,47,-90
    //13,47,-180
    //13,23,-180
    chassis.moveToPoint(18, 53, 2000, {.forwards=false, .maxSpeed=80}, false);
    pros::delay(200);
    chassis.turnToHeading(-119, 500, {.maxSpeed=65}, false);
    pros::delay(100)
    chassis.moveToPoint(9, 43, 2000, {.maxSpeed=90}, false);
    chassis.turnToHeading(-90, 500, {.maxSpeed=65}, false);
    pros::dealy(100)
    chassis.moveToPoint(13, 43, 2000, {.forwards=false, .maxSpeed=90}, true);
    pros::delay(100);
    chassis.turnToHeading(-180, 500, {.maxSpeed=65}, false);
    setIntake(0);
    pros::delay(100);
    chassis.moveToPoint(13, 23, 2000, {.maxSpeed=90}, false); 

    //Get Mobile Goal
     //16, 50, -119
     //11, 43, -90
    //chassis.setPose(47,36,55);
    //clamp.set_value(true);
    //tilt.set_value(true);
    //chassis.moveToPose(24,26,55,2000,{.forwards = false, .maxSpeed = 65}, false);
    //clamp.set_value(false);
    //pros::delay(10);
    //tilt.set_value(false);

//  //Get 2nd Ring
    //setIntake(115);
    //chassis.moveToPose(24,49,0,2000,{.maxSpeed = 105},true);

//  //Get 3rd and 4th Ring
//     chassis.turnToHeading(-90,1000,{}, true);
//     setIntake(111);
//    chassis.moveToPose(10,52,-90,1500,{.maxSpeed = 125},true);
//     chassis.moveToPoint(16,52,1500,{.forwards = false},true);
    // chassis.turnToHeading(120,1000,{},true);
   // chassis.moveToPose(10,45,-120,2000, {.maxSpeed = 125},true);
//     pros::delay(100);
//     intake.brake();

//     //Get 5th Ring
    //chassis.moveToPose(47,19,-61,3000,{.forwards = false, .minSpeed = 127},true);
//     pros::delay(100);
    //chassis.turnToHeading(180,1000);
//     pros::delay(100);
    //clamp.set_value(false);    
    //chassis.turnToHeading(-137, 1000, {}, false);
    //chassis.moveToPoint(29, 5, 2500, {.maxSpeed=50}, false);
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

// Latest version -- last updated Oct 6, 2024
void prog_skills_new()
{
    // Set Position
    chassis.setPose(-56, -7, -90);
    // Turn towards mobile goal
    chassis.turnToHeading(-30, 750, {});
    tilt.set_value(true);
    clamp.set_value(true);
    chassis.waitUntilDone();
    // Move towards & clamp mobile goal
    chassis.moveToPoint(-50, -19, 750, {.forwards=false, .maxSpeed=60}, false);
    chassis.moveToPoint(-48, -23, 750, {.forwards=false}, false);
    pros::delay(250);
    clamp.set_value(false);
    pros::delay(500);
    tilt.set_value(false);
    setIntake(127); // score preload
    // Turn towards ring #2
    chassis.turnToHeading(90, 750, {.maxSpeed=75}, false);
    // Move towards and intake ring #2
    chassis.moveToPoint(-24, -23, 1250, {.maxSpeed=60}, false);
    // Turn towards ring #3
    chassis.turnToHeading(180, 1000, {.maxSpeed=75}, false);
    // Move towards and intake ring #3
    chassis.moveToPoint(-24, -46, 1500, {}, false);
    // Turn towards ring #4
    chassis.turnToHeading(-90, 1200, {.maxSpeed=75}, false);
    // Move towards and intake ring #4
    chassis.moveToPoint(-44, -46, 1250, {}, false);
    // Move towards and intake ring #5
    chassis.moveToPoint(-58, -46, 1000, {}, false);
    // Turn towards ring #6
    chassis.turnToHeading(-225, 1000, {.maxSpeed=75}, false);
    // Move towards and intake  ring #6
    chassis.moveToPoint(-49, -55, 2000, {}, false);
    // Move to corner and drop Mobile Goal
    chassis.turnToHeading(60, 1000, {.maxSpeed=75}, false);
    chassis.moveToPoint(-53, -57, 1000, {.forwards=false}, false);
    tilt.set_value(true);
    clamp.set_value(true);
    pros::delay(250);

    // PART 2
    // Go to mobile goal #2 and clamp it
    chassis.moveToPoint(-47, -54, 1000, {}, false);
    chassis.turnToHeading(180, 1000, {.maxSpeed=75}, false);
    chassis.moveToPoint(-47, 13, 3500, {.forwards=false, .maxSpeed=80}, false);
    // chassis.moveToPoint(-47, 19, 1250, {.forwards=false, .maxSpeed=60}, false);
    chassis.moveToPoint(-47, 27, 1500, {.forwards=false});
    chassis.waitUntil(8);
    // pros::delay(250);
    clamp.set_value(false);
    pros::delay(500);
    tilt.set_value(false);
    pros::delay(250);
    chassis.waitUntilDone();
    // Turn to ring #1
    chassis.turnToHeading(90, 1000, {}, false);
    // Move to and intake ring #1
    setIntake(127);
    chassis.moveToPoint(-24, 24, 2000, {}, false);
    // Turn to ring #2
    chassis.turnToHeading(0, 1000, {}, false);
    // Move to and intake ring #2
    chassis.moveToPoint(-24, 45, 2000, {}, false);
    // Turn to ring #3
    chassis.turnToHeading(60, 1000, {}, false);
    // Move to and intake ring #3
    chassis.moveToPoint(2, 58, 2000, {}, false);
    // Move to and intake ring #4
    chassis.moveToPoint(-28, 43, 2000, {.forwards=false}, false);
    chassis.turnToHeading(-90, 1000, {}, false);
    chassis.moveToPoint(-44, 43, 2500, {}, false);
    // Move to and intake ring #5
    chassis.moveToPoint(-58, 43, 1500, {}, false);
    // Turn to ring #6
    chassis.turnToHeading(45, 1000, {}, false);
    // Move to and intake ring #6
    chassis.moveToPoint(-44, 57, 2000, {}, false);
    // Turn to corner
    chassis.turnToHeading(107, 1000, {}, false);
    // Place mobile goal #2 in corner
    chassis.moveToPoint(-52, 59, 1000, {.forwards=false}, false);
    tilt.set_value(true);
    clamp.set_value(true);

    // PART 3
    // Move to and intake ring #1
    chassis.moveToPose(24, 47, 90, 3000, {}, false);
    setIntake(0);
    // Move to and clamp mobile goal #3
    chassis.turnToHeading(-30, 1000, {}, false);
    chassis.moveToPoint(40, 15, 3500, {.forwards=false, .maxSpeed=80}, false);
    chassis.moveToPoint(46, 3, 1000, {.forwards=false});
    chassis.waitUntil(8);
    clamp.set_value(false);
    pros::delay(250);
    tilt.set_value(false);
    pros::delay(250);
    chassis.waitUntilDone();
    // Move to and intake ring #2
    chassis.turnToHeading(223, 1000, {}, false);
    chassis.moveToPoint(23, -23, 2000, {});
    setIntake(127);
    chassis.waitUntilDone();
    // Move to and intake ring #3
    chassis.turnToHeading(180, 1000, {}, false);
    chassis.moveToPoint(23, -46, 1500, {}, false);
    // Turn to ring #4
    chassis.turnToHeading(90, 1000, {}, false);

    /* ALL COORDINATES:
    -56, -7, -90
    -56, -7, -30
    -50, -19, -30
    -48, -23, -30
    -48, -23, 90
    -24, -23, 90
    -24, -23, 180
    -24, -46, 180
    -24, -46, -90
    -44, -46, -90
    -58, -46, -90
    -58, -46, -225
    -49, -55, -225
    -49, -55, -270
    -57, -56, 42
    -47, -46, 42
    -47, -46, 180
    -47, 24, 180
    -47, 24, 90
    -24, 24, 90
    -24, 24, 0
    -24, 47, 0
    -24, 47, 60
    -2, 58, 60
    -24, 47, 60
    -24, 47, -90
    -44, 47, -90
    -58, 47, -90
    -58, 47, 45
    -48, 57, 45
    -48, 57, 90
    -57, 58, 138
    */
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

void qualredmogoside() { 
    chassis.setPose(-48,-22,270);
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.moveToPose(-20, -21, 270, 1850, {.forwards = false, .maxSpeed = 65}, false);
    pros::delay(1000);
    clamp.set_value(false);
    tilt.set_value(false);
    pros::delay(500);
    setIntake(115);
    pros::delay(500);
    chassis.turnToHeading(180,1000);
    pros::delay(500);
    chassis.moveToPoint(-24,-46,1000,{},false);
    chassis.turnToHeading(0,1000);
    pros::delay(2000);
    for (int i = 0; i < 2; i++)
    {
        setDrive(6000,6000);
        pros::delay(200);
        setDrive(-6000, -6000);
        pros::delay(200);
    }
    setDrive(0, 0);
    pros::delay(1000);
    chassis.moveToPoint(-24,10,2000, {.maxSpeed = 50}, false);
    // clamp.set_value(true);
    pros::delay(3000);
    setIntake(0);
}

void qualbluemogoside() {
    chassis.setPose(48,-22,-270);
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.moveToPose(20, -21, -270, 1850, {.forwards = false, .maxSpeed = 65}, false);
    pros::delay(1000);
    clamp.set_value(false);
    tilt.set_value(false);
    pros::delay(500);
    setIntake(115);
    pros::delay(500);
    // for (int i = 0; i < 2; i++)
    // {
    //     setDrive(8000, 8000);
    //     pros::delay(200);
    //     setDrive(-8000, -8000);
    //     pros::delay(200);
    // }
    // setDrive(0, 0);
    // pros::delay(500);
    chassis.turnToHeading(180,1000);
    pros::delay(500);
    chassis.moveToPoint(24,-46,1000,{},false);
    // pros::delay(2000);
    chassis.turnToHeading(0,1000, {.maxSpeed=60}, false);
    pros::delay(2000);
    for (int i = 0; i < 2; i++)
    {
        setDrive(6000,6000);
        pros::delay(200);
        setDrive(-6000, -6000);
        pros::delay(200);
    }
    setDrive(0, 0);
    pros::delay(1000);
    chassis.moveToPoint(24,10,2000, {.maxSpeed = 50}, false);
    // clamp.set_value(true);
    // setIntake(0);
    // chassis.waitUntilDone();
    pros::delay(3000);
    setIntake(0);
}

void elimBlueMogoSide()
{  
    chassis.setPose(48,-22,-270);
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.moveToPose(20, -21, -270, 1850, {.forwards = false, .maxSpeed = 65}, false);
    pros::delay(1000);
    clamp.set_value(false);
    tilt.set_value(false);
    pros::delay(500);
    setIntake(115);
    pros::delay(500);

    chassis.turnToHeading(180,1000);
    pros::delay(500);
    chassis.moveToPoint(24,-46,1000,{},false);
    // pros::delay(2000);
    // chassis.turnToHeading(0,1000, {.maxSpeed=60}, false);
    pros::delay(1000);
    for (int i = 0; i < 2; i++)
    {
        setDrive(6000,6000);
        pros::delay(100);
        setDrive(-6000, -6000);
        pros::delay(100);
    }
    setDrive(0, 0);
    chassis.turnToHeading(110, 1000, {}, false);
    chassis.moveToPose(52, -52, 140, 3000, {}, false);
    pros::delay(400);
    setIntake(0);
    chassis.waitUntilDone();
    doinker.set_value(true);
    pros::delay(500);
    chassis.turnToHeading(195, 1000, {.minSpeed=120}, false);
    setIntake(-127);
}

void qual3ringblue() {

    //Get 1st Mogo and Score 2 Rings
    chassis.setPose(48,-22,270);
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.moveToPose(23, -21, 270, 1850, {.forwards = false, .minSpeed = 127});
    pros::delay(200);
    clamp.set_value(false);
    chassis.waitUntilDone();
    tilt.set_value(false);
    setIntake(115);
    pros::delay(500);
    chassis.turnToHeading(180,1000);
    pros::delay(500);
    chassis.moveToPoint(24,-46,1000,{},false);

    //Get 2nd Mogo
    chassis.moveToPose(36,2,180,2000,{.forwards = false, .minSpeed = 108},true);
    chassis.waitUntil(10);
    clamp.set_value(true);
    tilt.set_value(true);
    chassis.waitUntilDone();
    chassis.moveToPose(24,25,115,2000,{.forwards = false, .maxSpeed = 68},false);
    clamp.set_value(false);
    pros::delay(200);
    tilt.set_value(false);

    //Get Ring & Touch Ladder
    chassis.turnToHeading(0,1000);
    chassis.moveToPoint(24,46,1000, {.maxSpeed = 105});
    chassis.turnToHeading(180,1000);
    chassis.moveToPoint(24,12,1000, {.maxSpeed = 60});

}

// void soloauton_AWP_Blue_Positive(){
//     chassis.setPose(-37,-31,240);
//     chassis.moveToPoint(-33.5,-29,1000, {}, false);
//     clamp.set_value(false);
//     pros::delay(500);
//     tilt.set_value(false);
//     chassis.turnToPoint(-48,-46,1000);
//     setIntake(115);
//     chassis.waitUntilDone();
//     chassis.moveToPoint(-48,-46,1000, {}, false);
//     chassis.turnToPoint(-48,0,1000, {}, false);
//     chassis.moveToPoint(-48,0,1000, {}, false);
//     pros::delay(200);
//     chassis.moveToPoint(-48,20,500, {}, false);
//     setIntake(0);
//     clamp.set_value(true);
//     pros::delay(100);
//     tilt.set_value(true);
//     chassis.moveToPoint(-48,33.8,500, {}, false);
//     chassis.turnToHeading(300,500, {}, false);
//     chassis.moveToPoint(-24,24,500, {}, false);
//     clamp.set_value(false);
//     pros::delay(200);
//     tilt.set_value(false);
//     chassis.turnToPoint(-58,0, 1000, {}, false);
//     chassis.moveToPoint(-58,0, 2000, {}, false);
//     setIntake(115);
//     chassis.turnToHeading(90,500, {}, false);
//     chassis.moveToPoint(-29,0, 2000, {}, false);
// }

void soloauton_AWP_Blue_Negative(){
    chassis.setPose(49,24,90);
    chassis.moveToPoint(36,24,1000, {.forwards=false, .maxSpeed=60}, false);
    pros::delay(100);
    //FULL SPEED INTO GOAL
    chassis.moveToPoint(26,24,1000, {.forwards=false, .minSpeed=127}, true);
    chassis.waitUntil(6); //in inches
    //pros::delay(100);
    clamp.set_value(false);
    pros::delay(100);
    tilt.set_value(false);
    pros::delay(200);
    chassis.waitUntilDone();
    chassis.turnToPoint(24,40,1000);
    setIntake(115);
    chassis.waitUntilDone();
    chassis.moveToPoint(24,44,1200, {.maxSpeed=75}, false); //pikcup ring
    pros::delay(250);
    //chassis.turnToPoint(45,-24,1000, {}, false);
    chassis.turnToHeading(340,1000, {}, false);
    chassis.moveToPoint(45,-24,2000, {.forwards=false}, false); //switch sides
    //stop intake, drop gol
    setIntake(0);
    clamp.set_value(true);
    pros::delay(100);
    tilt.set_value(true);
    pros::delay(200);
    chassis.turnToHeading(90,500, {}, false);
    pros::delay(100);
    chassis.moveToPoint(36,-24,1000, {.forwards=false, .maxSpeed=60}, false);
    pros::delay(200);
    chassis.moveToPoint(26,-24,500, {.forwards=false, .minSpeed=127}, true); //zoom
    //pros::delay(100);
    clamp.set_value(false);
    pros::delay(100);
    tilt.set_value(false);
    pros::delay(200);
    chassis.turnToHeading(180,500, {}, false);
    setIntake(115);
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPoint(24,-44,1000, {.maxSpeed=75}, false);
    pros::delay(300);
    chassis.turnToHeading(0,500, {}, false);
    pros::delay(300);
    clamp.set_value(true);
    pros::delay(200);
    tilt.set_value(true);
    chassis.moveToPoint(24,-10,2000, {.maxSpeed=100}, false);


//     // chassis.moveToPoint(-24,24,500, {}, false);
//     // clamp.set_value(false);
//     // pros::delay(200);
//     // tilt.set_value(false);
//     // chassis.turnToPoint(-58,0, 1000, {}, false);
//     // chassis.moveToPoint(-58,0, 2000, {}, false);
//     // setIntake(115);
//     // chassis.turnToHeading(90,500, {}, false);
//     // chassis.moveToPoint(-29,0, 2000, {}, false);
}