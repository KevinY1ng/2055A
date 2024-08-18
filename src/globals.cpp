#include "main.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

int Motor_LF = -1;
int Motor_LM = -13;
int Motor_LB = -11;

int Motor_RF = 18;
int Motor_RM = 12;
int Motor_RB = 20;

// int inertial_PORT = 10;

//Inertial sensor
// pros::Imu Inertial(inertial_PORT);

//Drivetrain
pros::Motor drive_LF(-1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LM(-13, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LB(-11, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor drive_RF(18, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RM(12, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RB(20, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//MotorGroups
pros::MotorGroup Left_Drive({-11, -13, -1}, pros::v5::MotorGears::blue);
pros::MotorGroup Right_Drive({20, 12, 18}, pros::v5::MotorGears::blue);

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//Pneumatics
pros::adi::DigitalOut clamp('A', false);
pros::adi::DigitalOut tilt('B', false);

//inertial
pros::IMU imu(10);

lemlib::Drivetrain drivetrain(
    &Left_Drive, // left motor group
    &Right_Drive, // right motor group
    11.25, // 10 inch track width
    2.75, // using new 4" omnis
    450, // drivetrain rpm is 360
    2 // horizontal drift is 2 (for now)
);

lemlib::ControllerSettings linearController {
    40, // kP    
    0, // KI
    200, // kD 
    0, // anti windup
    1, // smallErrorRange
    300, // smallErrorTimeout
    3, // largeErrorRange
    600, // largeErrorTimeout
    5 // slew rate     //3
};
 
// turning PID
lemlib::ControllerSettings angularController {
    2.1, // kP
    0, // kI
    12, // kD
    3, // anti windup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    3 // slew rate
};

// odometry struct
lemlib::OdomSensors sensors {
    16, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    14, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    nullptr // &Inertial // inertial sensor
};

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);