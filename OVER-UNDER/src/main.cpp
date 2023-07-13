#include "main.h"
#include "electronics.h"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

void disabled() {}

void competition_initialize() {}

/**
 * @brief 
 * Autonomous code.
 */
void autonomous() {}

/**
 * @brief 
 * Driver control.
 */
void opcontrol() {
	while (true) {
		double ymotion = master.get_analog(ANALOG_LEFT_Y);
		double xmotion = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		double rotation = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		mtr_lf = ymotion + rotation;
		mtr_lb = ymotion + rotation;
		mtr_rf = ymotion - rotation;
		mtr_rb = ymotion - rotation;

		pros::lcd::set_text(1, std::to_string(ymotion));
		pros::lcd::set_text(2, std::to_string(rotation));

		pros::delay(10);
	}
}
