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

int MOTOR_LB = -11; //-11
int MOTOR_LM = -13; //-13
int MOTOR_LF = -1; //-1

int MOTOR_RB = 20; //20
int MOTOR_RM = 12; //12
int MOTOR_RF = 18; //18

int VERT_TRACKING = 14;
int HOR_TRACKING = 16;

int INERTIAL_PORT = 2;

// Pneumatics
char CLAMP_PORT = 'A';
char TILT_PORT = 'C';
char DOINKER_PORT = 'B';

int MOTOR_INTAKE_1 = -4; // bottom intake
int MOTOR_INTAKE_2 = -3; // top intake

int OPTICAL_SENSOR = 10;


//Drivetrain
pros::Motor drive_LB(MOTOR_LB, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LM(MOTOR_LM, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LF(MOTOR_LF, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor drive_RB(MOTOR_RB, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RM(MOTOR_RM, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RF(MOTOR_RF, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor intake1(MOTOR_INTAKE_1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor intake2(MOTOR_INTAKE_2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//MotorGroups
pros::MotorGroup Left_Drive({-11, -13, -1}, pros::v5::MotorGears::blue);
pros::MotorGroup Right_Drive({20, 12, 18}, pros::v5::MotorGears::blue);

//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//Pneumatics
pros::adi::DigitalOut tilt('A', true);
pros::adi::DigitalOut doinker('B', false);
pros::adi::DigitalOut clamp('C', false);

pros::Rotation vert_encoder(VERT_TRACKING);
pros::Rotation hort_encoder(HOR_TRACKING);

//inertial
pros::IMU imu(INERTIAL_PORT);

pros::Optical colorsensor(OPTICAL_SENSOR);

//Tracking Wheels
lemlib::TrackingWheel vert_tracking(&vert_encoder, 1.975, -0.39);
lemlib::TrackingWheel hort_tracking(&hort_encoder, 1.95, -0.3);

lemlib::Drivetrain drivetrain {
    &Left_Drive, // left motor group
    &Right_Drive, // right motor group
    11.5, // 10 inch track width
    2.75, // using new 4" omnis
    450, // drivetrain rpm is 360
    2 // horizontal drift is 2 (for now)
};

lemlib::ControllerSettings linearController {
    9, // kP    .// 990000     // 10 kP, 2 kD     // 9 kP, 0 kI, 3.5 kD | chassis.moveToPose(0, 48, 0, 5000, {.earlyExitRange = 2});  <-- these PID values with this function works really well
    0, // KI
    3.5, // kD //12900
    0, // anti windup
    0, // smallErrorRange // 0.3
    0, // smallErrorTimeout // 300
    0, // largeErrorRange // 3
    0, // largeErrorTimeout // 600 
    0 // slew rate  //5   //3
};
 
// turning PID
lemlib::ControllerSettings angularController {
    6.5, // kP         // 4 kP, 16 kD <-- last values that worked       // 5 kP, 22.5 kD <-- last values that worked //     6.5 kP, 30.5 kD <-- last values that worked     // we could fine-tune kP and kD more, but haven't yet
    0, // kI // 0.003
    30.5, // kD
    0, // anti windup // 3
    0, // smallErrorRange // 1
    0, // smallErrorTimeout // 100
    0, // largeErrorRange // 3
    0, // largeErrorTimeout // 500
    0 // slew rate // 3
};

// odometry struct
lemlib::OdomSensors sensors {
    &vert_tracking, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    &hort_tracking, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    &imu // &Inertial // inertial sensor
};

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);
