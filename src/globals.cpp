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

int MOTOR_LB = -11;
int MOTOR_LM = -13;
int MOTOR_LF = -1;

int MOTOR_RB = 20;
int MOTOR_RM = 12;
int MOTOR_RF = 18;

int VERT_TRACKING = 14;
int HOR_TRACKING = 16;

int INERTIAL_PORT = 4;

// Pneumatics
char CLAMP_PORT = 'A';
char TILT_PORT = 'B';


//Drivetrain
pros::Motor drive_LB(MOTOR_LB, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LM(MOTOR_LM, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LF(MOTOR_LF, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor drive_RB(MOTOR_RB, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RM(MOTOR_RM, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RF(MOTOR_RF, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);


//MotorGroups
pros::MotorGroup Left_Drive({-11, -13, -1}, pros::v5::MotorGears::blue);
pros::MotorGroup Right_Drive({20, 12, 18}, pros::v5::MotorGears::blue);

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//Pneumatics
pros::adi::DigitalOut clamp('A', false);
pros::adi::DigitalOut tilt('B', false);

pros::Rotation vert_encoder(VERT_TRACKING);
pros::Rotation hort_encoder(HOR_TRACKING);

//inertial
pros::IMU imu(10);

//Tracking Wheels
lemlib::TrackingWheel vert_tracking(&vert_encoder, lemlib::Omniwheel::NEW_2, -0.39);
lemlib::TrackingWheel hort_tracking(&hort_encoder, lemlib::Omniwheel::NEW_2, -0.3);

lemlib::Drivetrain drivetrain {
    &Left_Drive, // left motor group
    &Right_Drive, // right motor group
    11.25, // 10 inch track width
    2.75, // using new 4" omnis
    450, // drivetrain rpm is 360
    2 // horizontal drift is 2 (for now)
};

lemlib::ControllerSettings linearController {
    5, // kP    .
    0, // KI
    0, // kD 
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
    &vert_tracking, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    &hort_tracking, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    nullptr // &Inertial // inertial sensor
};

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);
