#include "main.h"
#include "auton.h"
#include "electronics.h"

// some global variables
bool wingState = false;
float drivePower = 0.9;
const double rotationPower = 0.7;
const double rotationCoefficient = (127*rotationPower)/pow(127, 3);

/*
P: Proportional to the position from the goal
I: Proportional to the sum of errors from the goal 
D: Proportional to the derivative of the position from the goal (velocity)
*/

// extern const lv_img_dsc_t funiiimage;

void initialize() {
	pros::lcd::initialize();
	/*lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img1, &funiiimage);
	lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, 0);*/
}

void disabled() {}

void competition_initialize() {}

/**
 * @brief 
 * Autonomous code.
 */
void autonomous() {
	bool autonSwitch = true;

	// match auton
	if (autonSwitch) moveStraight(48);
	else mtr_flywheel = -127;
}

/**
 * @brief 
 * Driver control.
 */
void opcontrol() {
	while (true) {
		// DRIVETRAIN
		double ymotion = master.get_analog(ANALOG_LEFT_Y);
		// quadratic turning	
		double rotation = rotationCoefficient * pow(master.get_analog(ANALOG_RIGHT_X), 3);
		
		left_drive = (ymotion + rotation) * drivePower;
		right_drive = (ymotion - rotation) * drivePower;

		// WINGS
		wings.set_value(master.get_digital(DIGITAL_L2));
		// INTAKE
		intake.set_value(master.get_digital(DIGITAL_R2));

		// FLYWHEEL
		if (master.get_digital(DIGITAL_B)) mtr_flywheel = -127;
		else mtr_flywheel = 0;
	}	
}