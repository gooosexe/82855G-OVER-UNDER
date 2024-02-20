#include "main.h"
#include "auton.h"
#include "electronics.h"

// some global variables
// 0 = skills
// 1 = close
// 2 = far
bool wingState = false;
float drivePower = 0.9;
const double rotationPower = 0.9;
const double rotationCoefficient = (127*rotationPower)/pow(127, 3);
int autonSwitch = 0;


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
		if (autonSwitch == 0) {
		skillsAuton();
	} else if (autonSwitch == 1) {
		closeAuton();
	} else if (autonSwitch == 2) {
		farAuton(1);
	}
}

/**
 * @brief 
 * Driver control.
 */
void opcontrol() {
	// flywheel pid loop variables
	double Kp = 3;
	double Ki = 0;
	double Kd = 0;
	double target = 250;
	double error, steadyStateError, prevError, errorRate, accel, curVel;
	double time = 0;
	while (true) {
		time++;
		// DRIVETRAIN
		double ymotion = master.get_analog(ANALOG_LEFT_Y);
		// quadratic turning	
		double rotation = rotationCoefficient * pow(master.get_analog(ANALOG_RIGHT_X), 3);

		left_drive = (ymotion + rotation) * drivePower;
		right_drive = 0.9*(ymotion - rotation) * drivePower;

		//blocker.set_value(master.get_digital(DIGITAL_A));

		// WINGS
		lwing.set_value(master.get_digital(DIGITAL_L2));
		rwing.set_value(master.get_digital(DIGITAL_R2));

		if (master.get_digital(DIGITAL_Y)) {
			hang.set_value(true);
		} else {
			hang.set_value(false);
		}
 
		// flywheel pid loop
		if (master.get_digital(DIGITAL_B)) {
			curVel = mtr_flywheel.get_actual_velocity();
			error = target - curVel;
			steadyStateError += error;
			errorRate = error - prevError;
			accel = Kp*error + Ki*steadyStateError + Kd*errorRate;
			mtr_flywheel.move_velocity(curVel + accel);	
			printf("%f,%f,300,%f\n", curVel, accel, time/100);
		} else {
			mtr_flywheel.move_velocity(0);
		}
		// HANG
		//hang.set_value(master.get_digital(DIGITAL_X));

		// INTAKE
		if (master.get_digital(DIGITAL_L1)) {
			mtr_intake = 127;
		}
		else if (master.get_digital(DIGITAL_R1)){
			mtr_intake = -127;
		} else {
			mtr_intake = -127;
		}

		prevError = error;
		pros::delay(10);
	}	
}