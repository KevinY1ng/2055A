#include "main.h"

// -------------------------------------------------------------------------------------------------
//PID Functions
// -------------------------------------------------------------------------------------------------

void turn(double targetheading, double maxspeed, float kP, float kI, float kD) {
    double currentheadibng = imu.get_rotation();
    double error = targetheading - currentheadibng;
    double errortotal = 0;
    float lasterror;
    double dT = 50;

    while (abs(error)>2) {
        double currentheading = imu.get_rotation();
        double error = targetheading - currentheading;

        if (error < 5 || error !=0) {
            errortotal += error;
        }
        else {
            errortotal = 0;
        }

        if (errortotal > 50 / kI) {
            errortotal = 50 / kI;
        }

        double proportional = kP * error;
        double integral = kI * errortotal;
        double derivative = (error - lasterror) / dT * kD;

        double preverror = error;

        double output = proportional + integral + derivative;

        drive_LF.move(output * maxspeed);
        drive_LM.move(output * maxspeed);
        drive_LB.move(output * maxspeed);

        drive_RF.move(output * -maxspeed);
        drive_RM.move(output * -maxspeed);
        drive_RB.move(output * -maxspeed);

        lasterror = error;

        pros::delay(50);
    }
      drive_LF.move(0);
        drive_LM.move(0);
        drive_LB.move(0);

        drive_RF.move(0);
        drive_RM.move(0);
        drive_RB.move(0);
}

void driveDistance(double targetdistance, double maxspeed, double kP, double kI, double kD) {
    const double pi = 3.14159;
    double tpr = 360;
    int ticks = ((drive_LF.get_position() + drive_LB.get_position()) / 2);
    double currentdistance = ((2.75*2) * pi) * (ticks / 360); //check teeth number on drivetrin
    double error = targetdistance - currentdistance;
    double preverror;
    double errortotal = 0;
    int dT = 50;

    while (error > 3) {
        int ticks = ((drive_LF.get_position() + drive_LB.get_position()) / 2);
        double currentdistance = ((2.75*2) * pi) * (ticks / 360);
        double error = targetdistance - currentdistance;

        if (error < 2 || error !=0) {
            errortotal =+ error;
        }
        else {
            errortotal = 0;
        }

        if (errortotal > (50/kI)) {
            errortotal = 50 / kI;
        }

        double porportional = error * kP;
        double integral = errortotal * kI;
        double derivative = (preverror - error) / dT * kD;

        double output = porportional + integral + derivative;

        preverror = error;

        drive_LF.move(maxspeed * output);
        drive_LM.move(maxspeed * output);
        drive_LB.move(maxspeed * output);

        drive_RF.move(maxspeed * output);
        drive_RM.move(maxspeed * output);
        drive_RB.move(maxspeed * output);

        pros::delay(50);
    }

    drive_LF.move(0);
    drive_LM.move(0);
    drive_LB.move(0);

    drive_RF.move(0);
    drive_RM.move(0);        
    drive_RB.move(0);
}

void swingleft(double radius, double angle, double maxspeed, double kP, double kI, double kD) {
   const double botwidth = 10;
   const double pi = 3.14159;
   const double dT = 50;
   double errortotal = 0;
   double preverror;

   double targetheadingleft = ((radius * 2 * pi ) * (angle / 360));
   double targetheadingright = (((radius + botwidth) * 2 * pi) * (angle / 360 ));

   double ticksleft = ((drive_LF.get_position() + drive_LB.get_position()) / 2);
   double ticksright = ((drive_RF.get_position() + drive_RB.get_position()) / 2);

   double currentheadingleft = (ticksleft / 360);
   double currentheadingright = (ticksright / 360);

   double errorleft = targetheadingleft - currentheadingleft;
   double errorright = targetheadingright - currentheadingright;

   while (errorleft > 2) {
    double targetheadingleft = ((radius * 2 * pi ) * (angle / 360));
    double ticksleft = ((drive_LF.get_position() + drive_LB.get_position()) / 2);
    double currentheadingleft = (ticksleft / 360);
    double errorleft = targetheadingleft - currentheadingleft;

    if (errorleft < 4 || errorleft!=0) {
        errortotal += errorleft;
    }
    else {
        errortotal = 0;
    }
    
    if (errortotal > (50 / kI) ) {
        errortotal = 50 / kI;
    }

    double porportional = errorleft * kP;
    double integral = errortotal * kI;
    double derivative = ((errorleft - preverror) / (dT * kD));

    preverror = errorleft;

    double output = porportional + integral + derivative;

    drive_LF.move(output * maxspeed);
    drive_LM.move(output * maxspeed);
    drive_LB.move(output * maxspeed);

    pros::delay(50);

   }

   while (errorright > 2) {
    double targetheadingright = (((radius+botwidth) * 2 * pi ) * (angle / 360));
    double ticksright = ((drive_RF.get_position() + drive_RB.get_position()) / 2);
    double currentheadingright = (ticksright / 360);
    double errorright = targetheadingright - currentheadingright;

    if (errorright < 4 || errorright!=0) {
        errortotal += errorright;
    }
    else {
        errortotal = 0;
    }
    
    if (errortotal > (50 / kI) ) {
        errortotal = 50 / kI;
    }

    double porportional = errorright * kP;
    double integral = errortotal * kI;
    double derivative = ((errorright - preverror) / (dT * kD));

    preverror = errorright;

    double output = porportional + integral + derivative;

    drive_RF.move(output * maxspeed);
    drive_RM.move(output * maxspeed);
    drive_RB.move(output * maxspeed);

    pros::delay(50);

   }

    drive_RF.move(0);
    drive_RM.move(0);
    drive_RB.move(0);

    drive_LF.move(0);
    drive_LM.move(0);
    drive_LB.move(0);
    
}

void swingright(double radius, double angle, double maxspeed, double kP, double kI, double kD) {
   const double botwidth = 10;
   const double pi = 3.14159;
   const double dT = 50;
   double errortotal = 0;
   double preverror;

   double targetheadingright = ((radius * 2 * pi ) * (angle / 360));
   double targetheadingleft = (((radius + botwidth) * 2 * pi) * (angle / 360 ));

   double ticksleft = ((drive_LF.get_position() + drive_LB.get_position()) / 2);
   double ticksright = ((drive_RF.get_position() + drive_RB.get_position()) / 2);

   double currentheadingleft = (ticksleft / 360);
   double currentheadingright = (ticksright / 360);

   double errorleft = targetheadingleft - currentheadingleft;
   double errorright = targetheadingright - currentheadingright;

   while (errorleft > 2) {
    double targetheadingleft = (((radius + botwidth) * 2 * pi ) * (angle / 360));
    double ticksleft = ((drive_LF.get_position() + drive_LB.get_position()) / 2);
    double currentheadingleft = (ticksleft / 360);
    double errorleft = targetheadingleft - currentheadingleft;

    if (errorleft < 4 || errorleft!=0) {
        errortotal += errorleft;
    }
    else {
        errortotal = 0;
    }
    
    if (errortotal > (50 / kI) ) {
        errortotal = 50 / kI;
    }

    double porportional = errorleft * kP;
    double integral = errortotal * kI;
    double derivative = ((errorleft - preverror) / (dT * kD));

    preverror = errorleft;

    double output = porportional + integral + derivative;

    drive_LF.move(output * maxspeed);
    drive_LM.move(output * maxspeed);
    drive_LB.move(output * maxspeed);

    pros::delay(50);

   }

   while (errorright > 2) {
    double targetheadingright = ((radius * 2 * pi ) * (angle / 360));
    double ticksright = ((drive_RF.get_position() + drive_RB.get_position()) / 2);
    double currentheadingright = (ticksright / 360);
    double errorright = targetheadingright - currentheadingright;

    if (errorright < 4 || errorright!=0) {
        errortotal += errorright;
    }
    else {
        errortotal = 0;
    }
    
    if (errortotal > (50 / kI) ) {
        errortotal = 50 / kI;
    }

    double porportional = errorright * kP;
    double integral = errortotal * kI;
    double derivative = ((errorright - preverror) / (dT * kD));

    preverror = errorright;

    double output = porportional + integral + derivative;

    drive_RF.move(output * maxspeed);
    drive_RM.move(output * maxspeed);
    drive_RB.move(output * maxspeed);

    pros::delay(50);

   }

    drive_RF.move(0);
    drive_RM.move(0);
    drive_RB.move(0);

    drive_LF.move(0);
    drive_LM.move(0);
    drive_LB.move(0);
    
}