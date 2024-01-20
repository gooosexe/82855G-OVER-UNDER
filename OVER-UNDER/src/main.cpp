#include "main.h"
#include "auton.h"
#include "electronics.h"

// some global variables
bool wingState = false;
float drivePower = 0.9;
const double rotationPower = 0.9;
const double rotationCoefficient = (127*rotationPower)/pow(127, 3);


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
	//auton switch
	// 0 = skills
	// 1 = close
	// 2 = far
	int autonSwitch = 1;

	if (autonSwitch == 0) {
		skillsAuton();
	} else if (autonSwitch == 1) {
		closeAuton();
	} else if (autonSwitch == 2) {
		farAuton();
	}

	// match auton
	//if (autonSwitch) moveStraight(48);
	//else mtr_flywheel = -127;
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
		if (master.get_digital(DIGITAL_L1)) {
			mtr_intake = 127;
		}
		else if (master.get_digital(DIGITAL_R1)){
			mtr_intake = -127;
		} else {
			mtr_intake = -60;
		}

		// FLYWHEEL
		if (master.get_digital(DIGITAL_B)) mtr_flywheel = -127;
		else mtr_flywheel = 0;
	}	

}