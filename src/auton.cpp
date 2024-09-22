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
    sortRed(127, 10000);   
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
        chassis.moveToPoint(29, 24, 2500, {.forwards=false, .maxSpeed=65}, false);
        pros::delay(500);
        clamp.set_value(false);
        tilt.set_value(false);
        pros::delay(500);
        setIntake(127);
        pros::delay(2000);
        chassis.turnToHeading(0, 1000, {.maxSpeed=65}, false);
        chassis.moveToPoint(24, 47, 3000, {}, false);
        chassis.turnToHeading(180, 2000, {.maxSpeed=65}, false);
        chassis.moveToPoint(24, 6, 5000, {.maxSpeed=70}, false);
    // //Get Mobile Goal
//     chassis.setPose(47,36,55);
//     clamp.set_value(true);
//     tilt.set_value(true);
//     chassis.moveToPose(24,26,55,2000,{.forwards = false, .maxSpeed = 65}, false);
//     clamp.set_value(false);
//     pros::delay(10);
//     tilt.set_value(false);

// //  //Get 2nd Ring
//     setIntake(115);
//     chassis.moveToPose(24,49,0,2000,{.maxSpeed = 105},true);

// //  //Get 3rd and 4th Ring
//     chassis.turnToHeading(-90,1000,{}, true);
//     setIntake(111);
//     chassis.moveToPose(10,52,-90,1500,{.maxSpeed = 125},true);
//     chassis.moveToPoint(16,52,1500,{.forwards = false},true);
//     // chassis.turnToHeading(120,1000,{},true);
//     chassis.moveToPose(10,45,-120,2000, {.maxSpeed = 125},true);
// //     pros::delay(100);
// //     intake.brake();

// //     //Get 5th Ring
//     chassis.moveToPose(47,19,-61,3000,{.forwards = false, .minSpeed = 127},true);
// //     pros::delay(100);
//     chassis.turnToHeading(180,1000);
// //     pros::delay(100);
//     clamp.set_value(false);    
//     chassis.turnToHeading(-137, 1000, {}, false);
//     chassis.moveToPoint(29, 5, 2500, {.maxSpeed=50}, false);
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
