#include "main.h"
#include "electronics.h"

// some global variables
bool wingState = false;

// yeah i dont think we'll ever need this
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
		double rotation = master.get_analog(ANALOG_RIGHT_X);

		// if (master.get_digital(DIGITAL_L1)) {
		// 	wingState = !wingState;
		// 	wings.set_value(wingState);
		// }

		wings.set_value(master.get_digital(DIGITAL_L2));

		if (master.get_digital(DIGITAL_B)) mtr_flywheel = 128;
		else mtr_flywheel = 0;

		left_drive = (ymotion + rotation)*0.9;
		right_drive = (ymotion - rotation) * 0.9;

		pros::lcd::set_text(1, std::to_string(ymotion));
		pros::lcd::set_text(2, std::to_string(rotation));
	}	
}