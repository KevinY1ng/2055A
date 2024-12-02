#include "main.h"
#include "pros/adi.hpp"
#include "pros/gps.h"
#include "pros/gps.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/vision.hpp"
#include "lemlib/api.hpp"
#include <cstddef>

int MOTOR_LB = -9; //-11
int MOTOR_LM = -10; //-13
int MOTOR_LF = -19; //-1

int MOTOR_RB = 18; //20
int MOTOR_RM = 8; //12
int MOTOR_RF = 6; //18

int VERT_TRACKING_PORT = -4;
int HOR_TRACKING_PORT = 16;

int INERTIAL_PORT = 12;

// Pneumatics
char CLAMP_PORT = 'H';
char CLAW_PORT = 'G';
char DOINKER_PORT = 'F';


int MOTOR_INTAKE_1= 7; // bottom intake
int ARM_PORT = 1;
int arm_sensor = 11;
// int MOTOR_INTAKE_2 = -3; // top intake

int COLOR_SENSOR_PORT = 20; // 


//Drivetrain
pros::Motor drive_LB(MOTOR_LB, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LM(MOTOR_LM, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LF(MOTOR_LF, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor drive_RB(MOTOR_RB, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RM(MOTOR_RM, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RF(MOTOR_RF, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor intake1(MOTOR_INTAKE_1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor arm(ARM_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
// pros::Motor intake2(MOTOR_INTAKE_2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//MotorGroups
pros::MotorGroup Left_Drive({-9, -10, -19}, pros::v5::MotorGears::blue);
pros::MotorGroup Right_Drive({18, 8, 6}, pros::v5::MotorGears::blue);

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//Pneumatics
// pros::adi::DigitalOut tilt('A', true);
// pros::adi::DigitalOut doinker('B', false);
pros::adi::DigitalOut clamp('H', true);
pros::adi::DigitalOut claw(CLAW_PORT, false);
pros::adi::DigitalOut doinker('F', false);


pros::Rotation vert_encoder(VERT_TRACKING_PORT);
pros::Rotation hort_encoder(HOR_TRACKING_PORT);
pros::Rotation armsensor(arm_sensor);

//inertial
pros::IMU imu(INERTIAL_PORT);

// pros::Optical colorsensor(OPTICAL_SENSOR);
pros::Optical colorsensor(COLOR_SENSOR_PORT);

//Tracking Wheels
lemlib::TrackingWheel vert_tracking(&vert_encoder, 1.975, -0.75); // 0.75 inches left of the tracking center
lemlib::TrackingWheel hort_tracking(&hort_encoder, 1.95, 0.75); // 0.75 inches forward of tracking center

lemlib::Drivetrain drivetrain {
    &Left_Drive, // left motor group
    &Right_Drive, // right motor group
    11.5, // 10 inch track width
    2.5, // using new 4" omnis
    450, // drivetrain rpm is 360
    2 // horizontal drift is 2 (for now)
};

lemlib::ControllerSettings linearController {
    0, // proportional gain (kP)
    0, // integral gain (kI)
    0, // derivative gain (kD)
    0, // anti windup
    0, // small error range, in inches
    0, // small error range timeout, in milliseconds
    0, // large error range, in inches
    0, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
};
 
 // 1, 0, 25 <-- last values that worked      // 1.25, 46, 0   // 1.5, 50, 0
// turning PID
lemlib::ControllerSettings angularController {
    0.6, // proportional gain (kP)
    0, // integral gain (kI)
    1.5, // derivative gain (kD)
    0, // anti windup
    0, // small error range, in degrees
    0, // small error range timeout, in milliseconds
    0, // large error range, in degrees
    0, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
};

/*
list:
0.5, 0, 0
*/

// odometry struct
lemlib::OdomSensors sensors {
    &vert_tracking, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    &hort_tracking, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    &imu // &Inertial // inertial sensor
};

// create the chassis
lemlib::Chassis chassis(drivetrain, 
                        linearController, 
                        angularController, 
                        sensors
);

