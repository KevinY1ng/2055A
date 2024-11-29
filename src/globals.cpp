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

int VERT_TRACKING_PORT = 4;
int HOR_TRACKING_PORT = 16;

int INERTIAL_PORT = 2;

// Pneumatics
char CLAMP_PORT = 'A';
// char TILT_PORT = 'C';
// char DOINKER_PORT = 'B';

int MOTOR_INTAKE_1= 7; // bottom intake
int ARM_PORT = 1;
// int MOTOR_INTAKE_2 = -3; // top intake


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
pros::MotorGroup Left_Drive({9, 10, 19}, pros::v5::MotorGears::blue);
pros::MotorGroup Right_Drive({18, 8, 6}, pros::v5::MotorGears::blue);

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//Pneumatics
// pros::adi::DigitalOut tilt('A', true);
// pros::adi::DigitalOut doinker('B', false);
pros::adi::DigitalOut clamp('H', true);

pros::Rotation vert_encoder(VERT_TRACKING_PORT);
pros::Rotation hort_encoder(HOR_TRACKING_PORT);

//inertial
// pros::IMU imu(INERTIAL_PORT);

// pros::Optical colorsensor(OPTICAL_SENSOR);

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
    10, // proportional gain (kP)
    0, // integral gain (kI)
    3, // derivative gain (kD)
    3, // anti windup
    1, // small error range, in inches
    100, // small error range timeout, in milliseconds
    3, // large error range, in inches
    500, // large error range timeout, in milliseconds
    20 // maximum acceleration (slew)
};
 
// turning PID
lemlib::ControllerSettings angularController {
    2, // proportional gain (kP)
    0, // integral gain (kI)
    10, // derivative gain (kD)
    0, // anti windup
    0, // small error range, in degrees
    0, // small error range timeout, in milliseconds
    0, // large error range, in degrees
    0, // large error range timeout, in milliseconds
    0 // maximum acceleration (slew)
};

// odometry struct
lemlib::OdomSensors sensors {
    &vert_tracking, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    &hort_tracking, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    nullptr // &Inertial // inertial sensor
};

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);
