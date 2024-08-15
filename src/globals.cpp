#include "main.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

int Motor_LF = 1;
int Motor_LM = 2;
int Motor_LB = 3;

int Motor_RF = 4;
int Motor_RM = 5;
int Motor_RB = 6;

//Drivetrain
pros::Motor drive_LF(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LM(2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_LB(3, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor drive_RF(4, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RM(5, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor drive_RB(6, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

//MotorGroups
pros::MotorGroup Left_Drive({1,2,3},pros::v5::MotorGears::blue);
pros::MotorGroup Right_Drive({4,5,6},pros::v5::MotorGears::blue);

//Controller
pros::Controller controller1(pros::E_CONTROLLER_MASTER);

//Pneumatics
pros::adi::DigitalOut clamp('A', false);
pros::adi::DigitalOut tilt('B', false);

