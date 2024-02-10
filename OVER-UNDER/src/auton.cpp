#include "electronics.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio>

#define M_PI 3.14159265358979323846 

// PID constants
const double kP = 5;

const double kD = 1.5; // 1.5
const double kI = 0.04; // 0.04
const double kPt = 2;
const double kDt = 2;
const double kIt = 0;
// Smallest distance from the goal
double errorLimit = 0.05;
int countCheck = 0;
// PID Variables
// velocity in inches per second

double velocity, error, prevError, steadyStateError, errorRate;

std::fstream posDataCSV;

void resetPosition() {
	mtr_lf.tare_position();
	mtr_lb.tare_position();
	mtr_rf.tare_position();
	mtr_rb.tare_position();
	mtr_lbh.tare_position();
	mtr_rbh.tare_position();
}

/**
 * @brief
 * Retrieves the average position of the robot.
 * @return double 
 */
double getAveragePosition() {
	//printf("%d,%d,%d,%d,%d,%d\n", mtr_lf.get_position(), mtr_lb.get_position(), mtr_lfh.get_position(), mtr_rf.get_position(), mtr_rb.get_position(), mtr_rfh.get_position());
	// get average position of all motors (excluding top motors)
	//double avgMotorRot = (left_drive.get_position() + right_drive.get_position())/2;
	double avgMotorRot = (mtr_lf.get_position() + mtr_lb.get_position() + mtr_lbh.get_position() + mtr_rf.get_position() + mtr_rb.get_position() + mtr_rbh.get_position())/6;
	return 3.25*M_PI*avgMotorRot*(3.0/5.0);
}

/**
 * @brief 
 * Records some useful metrics into a CSV file.q
 */
void recordData() {
	printf("%f,%f,%f\n", error, errorRate, velocity);
}


/*
P: Proportional to the position from the goal
I: Proportional to the sum of errors from the goal 
D: Proportional to the derivative of the position from the goal (velocity)
*/

/**
 * @brief 
 * Moves the bot in a straight line.
 * @param distance in inches
 */
void moveStraight(double distance) {
	resetPosition();
	steadyStateError = 0;
	error = distance;
	prevError = error;
	while (countCheck < 40) {

		countCheck++;

		// distance subtracted by the average of the four ground motors
		error = distance - getAveragePosition();

		errorRate = error - prevError;
		steadyStateError += error;
		velocity = kP*error + kD*errorRate + kI*steadyStateError;

		left_drive = velocity;
		right_drive = 0.9*velocity;

		recordData();

		pros::lcd::print(1, "error: %f", error);
		pros::lcd::print(2, "error rate: %f", errorRate);
		pros::lcd::print(3, "steadyStateError: %f", steadyStateError);
		pros::lcd::print(5, "velocity: %f", velocity);

		prevError = error;
		pros::delay(20);
	}	
	countCheck = 0;
	left_drive = 0;
	right_drive = 0;
}

/**
 * @brief 
 * Turns the bot in place.
 * @param degrees self explanatory
 */
void turn(double degrees, double time) {
	imu_1.tare_heading();
	imu_2.tare_heading();
	printf("imu_1: %f\n", imu_1.get_heading());
	printf("imu_2: %f\n", imu_2.get_heading());

	steadyStateError = 0;
	error = degrees;
	prevError = error;
	double averageHeading, heading1, heading2;

	while (error > 0.5) {
		countCheck++;
		// distance subtracted by the average of the four ground motors
		heading1 = imu_1.get_heading();
		heading2 = imu_2.get_heading();
		if (degrees != 180) {
			if (heading1 > 180) heading1 -= 360;
			if (heading2 > 180) heading2 -= 360;
		}

		averageHeading = (heading1 + heading2)/2;
		error = std::abs(degrees) - std::abs(averageHeading);
		errorRate = error - prevError;
		steadyStateError += error;
		// using angular velocity instead of linear velocity
		velocity = kPt*error + kDt*errorRate + kIt*steadyStateError;
		if (velocity > 100) velocity = 100;	
		// if degrees is positive, turn right
		if (degrees > 0) {
			left_drive = velocity;
			right_drive = -velocity;
		// if degrees is negative, turn right
		} else {
			left_drive = -velocity;
			right_drive = velocity;
		}
		/*
		printf("%f,%f,%f,%f,%f\n", averageHeading, error, errorRate, velocity, steadyStateError);
		pros::lcd::print(0,"error: %f", averageHeading);
		pros::lcd::print(2, "error rate: %f", errorRate);
		pros::lcd::print(3, "steadyStateError: %f", steadyStateError);
		pros::lcd::print(5, "velocity: %f", velocity);*/

		prevError = error;
		pros::delay(20);
	}
	countCheck = 0;
	left_drive = 0;
	right_drive = 0;
}

void skillsAuton(){
	for (int i = 0; i < 8; i++) {
		moveStraight(60);
		pros::delay(20);
		moveStraight(-60);
		pros::delay(5000);
	}
}

void closeAuton(){
	// goal is AWP
	mtr_intake.move(10);
	moveStraight(-40);
	turn(-20, 750);
	moveStraight(24);
	pros::delay(100);
	wings.set_value(true);
	pros::delay(100);
	turn(-30, 750);
	moveStraight(10);
	wings.set_value(false);
	turn(-25, 750);
	moveStraight(48);
}

void farAuton(int type) {
	switch (type) {
		case 0:
			mtr_intake = 127;
			pros::delay(100);
			mtr_intake = -127;

			moveStraight(30);
			mtr_intake = 127; // deposit preload

			turn(-90, 1000);
			mtr_intake = -127;
			moveStraight(24); // intake ball 1
			
			turn(135, 1000); //deposit
			moveStraight(24);
			mtr_intake = 127;

			moveStraight(-10);
			turn(-90, 1000);
			mtr_intake = -127; // intake
			moveStraight(15);
			turn(135, 1000);

			//wings
			wings.set_value(true);
			moveStraight(50);
			moveStraight(-20);
			moveStraight(30);
			moveStraight(-20);
			moveStraight(30);
			break;
		case 1: // old auton
			mtr_intake = 127;
			pros::delay(100);
			mtr_intake = -127;
			moveStraight(45);
			turn(90, 1000);
			moveStraight(30);
			turn(-130, 750);
			moveStraight(15);
			turn(135, 750);
			moveStraight(50);
			/*moveStraight(-10);
			turn(180, 2000);
			moveStraight(50);
			turn(170, 2000);
			moveStraight(50);*/
			break;
	}
}

