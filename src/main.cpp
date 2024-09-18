#include "main.h"
#include "lemlib/api.hpp"
#include "lemlib/pose.hpp"


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void colorsortred() {
	double colorvalue;
	while (true) {
		colorvalue = colorsensor.get_hue();
		pros::lcd::set_text(3, std::to_string(colorsensor.get_hue()));
		if (colorvalue >= 195 && colorvalue <= 230) { 
			pros::lcd::set_text(4, "BLUE RING DETECTED :(");
			intake1.move(127);
			intake2.move(-127);
			pros::delay(1800);
		}
		else if (colorvalue >= 350 && colorvalue <= 360 || colorvalue >= 0 && colorvalue <= 10) {
			pros::delay(500);
			setIntake(127);
		}
		else
		{
			driveIntake();
		}

		
		pros::delay(20);
	}
}


void colorsortblue()
{
	double colorvalue;
	while (true)
	{
		colorvalue = colorsensor.get_hue();
		pros::lcd::set_text(3, std::to_string(colorvalue));
		if (colorvalue >= 0 && colorvalue <= 30) { 
			pros::lcd::set_text(4, "RED RING DETECTED :(");
			intake1.move(127);
			intake2.move(-127);
			pros::delay(1800);
		}
		else
		{
			driveIntake();
		}
		
		pros::delay(20);
	}
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	drive_LB.set_brake_mode(MOTOR_BRAKE_HOLD);
	drive_LM.set_brake_mode(MOTOR_BRAKE_HOLD);
    drive_LF.set_brake_mode(MOTOR_BRAKE_HOLD);

    drive_RB.set_brake_mode(MOTOR_BRAKE_HOLD);
	drive_RM.set_brake_mode(MOTOR_BRAKE_HOLD);
    drive_RF.set_brake_mode(MOTOR_BRAKE_HOLD);

	pros::lcd::register_btn1_cb(on_center_button);
	chassis.calibrate();
	// pros::Task my_task(colorsortblue);

	// pros::Task screen_task([&]() {
	// 	double colorvalue;
	// 	while (true) {
	// 		colorvalue = colorsensor.get_hue();
	// 		pros::lcd::set_text(4, std::to_string(colorvalue));
	// 		pros::delay(20);
	// 	}
    // });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	
	// PID_Test();
	// straightTest();
	// PID_Turn();
	// mogo_rush(); // SLOT 3
	// mogo_rushright(); // SLOT 6
	// auton_test(); // SLOT 1
	//elim5ring(); //SLOT 4
	// soloawp(); //slot 5 
	progskills();//SLOT 8
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	drive_LB.set_brake_mode(MOTOR_BRAKE_COAST);
	drive_LM.set_brake_mode(MOTOR_BRAKE_COAST);
    drive_LF.set_brake_mode(MOTOR_BRAKE_COAST);

    drive_RB.set_brake_mode(MOTOR_BRAKE_COAST);
	drive_RM.set_brake_mode(MOTOR_BRAKE_COAST);
    drive_RF.set_brake_mode(MOTOR_BRAKE_COAST);

	// pros::Task my_task(colorsortblue);

	// pros::rtos::Task my_task(my_task_fn);


	// pros::Task screen_task([&]() {
    //     while (true) {
    //         // print robot location to the brain screen
	// 		pros::lcd::set_text(5, "X: "  +  std::to_string(chassis.getPose().x)); // print the x position
    //         pros::lcd::set_text(6, "Y: " + std::to_string(chassis.getPose().y)); // print the y position
    //     	//pros::lcd::set_text(7, "Angle: " + std::to_string(chassis.getPose().theta)); // print the heading
    //         // delay to save resources
    //         pros::delay(20);
    //     }
    // });

	my_opcontrol();

}
