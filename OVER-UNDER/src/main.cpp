#include "main.h"
#include <iostream>
#include "api.h"
#include "pros/llemu.hpp"



pros::Controller master (pros::E_CONTROLLER_MASTER);
pros::Motor mtr_lf(3);
pros::Motor mtr_lb(9);
pros::Motor mtr_rf(6); 
pros::Motor mtr_rb(7);


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

void autonomous() {}

void opcontrol() {
	while (true) {
		/*int ymotion = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rotation = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);*/

		double ymotion = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        double xmotion = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
        double rotation = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		mtr_lf = ymotion + rotation;
		mtr_lb = ymotion + rotation;
		mtr_rf = ymotion - rotation;
		mtr_rb = ymotion - rotation;

		pros::lcd::set_text(1, std::to_string(ymotion));
		pros::lcd::set_text(2, std::to_string(rotation));

		pros::delay(5);
	}
}
