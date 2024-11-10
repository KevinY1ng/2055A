#include "main.h"
#include "EZ-Template/api.hpp"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "pros/vision.h"
// #include "lvgl/lvgl.h"
#include <string>


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


void color_sort_red_team() {
	double colorvalue;
	while (true) {
		colorvalue = colorsensor.get_hue();
		pros::lcd::set_text(3, std::to_string(colorvalue));
		if (colorvalue >= 150 && colorvalue <= 200)
		{
			pros::lcd::set_text(4, "BLUE RING DETECTED! :(");
			// pros::delay(5);
			intake1.move(127);
			intake2.move(-127);
			pros::delay(600);
			//setIntake(0);
		}

		else {
			driveIntake();
		}
		pros::delay(20);
	}
}

void color_sort_blue_team() {
	double colorvalue;
	while (true) {
		colorvalue = colorsensor.get_hue();
		pros::lcd::set_text(3, std::to_string(colorvalue));
		if (colorvalue >= 0 && colorvalue <= 20)
		{
			pros::lcd::set_text(4, "RED RING DETECTED! :(");
			// pros::delay(5);
			intake1.move(127);
			intake2.move(-127);
			pros::delay(600);
			//setIntake(0);
		}

		else {
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
	chassis.calibrate();
	pros::lcd::initialize();

	drive_LB.set_brake_mode(MOTOR_BRAKE_HOLD);
	drive_LM.set_brake_mode(MOTOR_BRAKE_HOLD);
    drive_LF.set_brake_mode(MOTOR_BRAKE_HOLD);

    drive_RB.set_brake_mode(MOTOR_BRAKE_HOLD);
	drive_RM.set_brake_mode(MOTOR_BRAKE_HOLD);
    drive_RF.set_brake_mode(MOTOR_BRAKE_HOLD);

	pros::lcd::register_btn1_cb(on_center_button);

	lvgl_init();

	// pros::Task my_task(my_task_fn);

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
	
	// soloauton_AWP_Blue_Negative(); // SLOT 2
	// soloauton_AWP_Red_Negative(); // SLOT 1
	//qual5ringRed(); // SLOT 3 angle
	qual5ringBlue(); // SLOT 4 straight
	//elim5ringRed(); // SLOT 1
	// auton_test(); // SLOT 7
	// mogo_rush(); // SLOT 3
	//mogo_rushright(); // SLOT 6
	//elim5ringBlue(); //SLOT 2
	//qualredmogoside(); //slot 5 
	//qualbluemogoside(); //slot 6
	//elimBlueMogoSide();//SLOT 8
	//  prog_skills_new(); // SLOT 8

// 	Auton selector;
//     switch (selector::auton) {
//         case 1:
// 			soloauton_AWP_Blue_Negative();
//             // Safe 5 Triball Auton
//             // offense_auton_safe();
//             break;

//         case 2:
//             // 
//             // offense_last_min();
//             // offense_auton_midrush_new();
//             break;

//         case 3:
//             // offense_auton_6balls_v2();
//             break;
        
//         case -1:
//             // Safe
//             // defense_awp();
//             break;
        
//         case -2:
//             // Midrush
//             // defense_last_min();
//             break;

//         case -3:
//             // Max Potential
//             // defense_auton_max_potential();
//             break;

//         case 0:
//             prog_skills_new();
//             break;
//     } 
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
	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(on_center_button);
	// while (true) {
	// 	pros::lcd::set_text(1,"Hello World");
	// }
	drive_LB.set_brake_mode(MOTOR_BRAKE_COAST);
	drive_LM.set_brake_mode(MOTOR_BRAKE_COAST);
    drive_LF.set_brake_mode(MOTOR_BRAKE_COAST);

    drive_RB.set_brake_mode(MOTOR_BRAKE_COAST);
	drive_RM.set_brake_mode(MOTOR_BRAKE_COAST);
    drive_RF.set_brake_mode(MOTOR_BRAKE_COAST);

	// pros::lcd::set_text(3, std::to_string(colorsensor.get_hue()));

	// pros::rtos::Task my_task(color_sort_red);


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

	// pros::rtos::Task my_task(color_sort_blue_team);
	// pros::rtos::Task my_task(color_sort_red_team);
	my_opcontrol();

}
