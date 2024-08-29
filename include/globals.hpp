#include "main.h"
#include "lemlib/chassis/chassis.hpp"


extern pros::Imu Inertial;

//drivetrain
extern pros::Motor drive_LF;
extern pros::Motor drive_LM;
extern pros::Motor drive_LB;

extern pros::Motor drive_RF;
extern pros::Motor drive_RM;
extern pros::Motor drive_RB;

//MotorGroups
extern pros::MotorGroup Left_Drive;
extern pros::MotorGroup Right_Drive;


//Controller
extern pros::Controller controller;

//Pneumatics
extern pros::adi::DigitalOut clamp;
extern pros::adi::DigitalOut tilt;

extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;
extern lemlib::OdomSensors sensors;
extern lemlib::Chassis chassis;

extern pros::Rotation vert_encoder;
extern pros::Rotation hort_encoder;

extern pros::IMU imu;

extern pros::Motor intake;


