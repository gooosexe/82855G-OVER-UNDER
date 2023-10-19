#include "main.h"
#include "electronics.h"

// some global variables
bool armState = false;


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

		if (master.get_digital(DIGITAL_L1)) {
			// flip arm state
			armState = !armState;
			(armState) ? armLeft.set_value(true) : armLeft.set_value(false);
		}

		if (master.get_digital(DIGITAL_A)) mtr_cata.move_absolute(mtr_cata.get_position() + 180, 1000); 

		left_drive = (ymotion + rotation)*0.9;
		right_drive = (ymotion - rotation)*0.9;

		pros::lcd::set_text(1, std::to_string(ymotion));
		pros::lcd::set_text(2, std::to_string(rotation));

		pros::delay(10);
	}
}
