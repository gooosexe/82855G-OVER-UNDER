#include "electronics.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio>

#define M_PI 3.14159265358979323846 

// PID constants
const double kP = 4;
const double kD = 0.8;
const double kI = 0.01;
const double kPt = 0.5;
const double kDt = 2;
const double kIt = 0.01;
// Smallest distance from the goal
double errorLimit = 0.25;
double errorLimitAngle = 0.5;
// PID Variables
// velocity in inches per second

double velocity, error, prevError, steadyStateError, errorRate;

std::fstream posDataCSV;

void resetPosition() {
	mtr_lf.tare_position();
	mtr_lb.tare_position();
	mtr_rf.tare_position();
	mtr_rb.tare_position();
	mtr_lfh.tare_position();
	mtr_rfh.tare_position();
}

/**
 * @brief
 * Retrieves the average position of the robot.
 * @return double 
 */
double getAveragePosition() {
	// get average position of all motors (excluding top motors)
	double avgMotorRot = (mtr_lf.get_position() + mtr_lb.get_position() + mtr_lfh.get_position() + mtr_rf.get_position() + mtr_rb.get_position() + mtr_rfh.get_position())/6;
	return 3.25*M_PI*avgMotorRot*(3.0/5.0);
}

/**
 * @brief 
 * Records some useful metrics into a CSV file.
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
	while (std::abs(error) > errorLimit) {
		// distance subtracted by the average of the four ground motors
		error = distance - getAveragePosition();

		errorRate = error - prevError;
		steadyStateError += error;
		velocity = kP*error + kD*errorRate + kI*steadyStateError;

		left_drive = velocity;
		right_drive = velocity;

		recordData();

		pros::lcd::print(1, "error: %f", error);
		pros::lcd::print(2, "error rate: %f", errorRate);
		pros::lcd::print(3, "steadyStateError: %f", steadyStateError);
		pros::lcd::print(5, "velocity: %f", velocity);

		prevError = error;
		pros::delay(20);
	}	
	left_drive = 0;
	right_drive = 0;
}

/**
 * @brief 
 * Turns the bot in place.
 * @param degrees self explanatory
 */
void turn(double degrees) {
	imu_1.tare_heading();
	imu_2.tare_heading();

	steadyStateError = 0;
	error = degrees;
	prevError = error;
	double averageHeading, heading1, heading2;

	while (std::abs(error) > errorLimitAngle) {
		// distance subtracted by the average of the four ground motors
		heading1 = imu_1.get_heading();
		heading2 = imu_2.get_heading();
		if (heading1 > 180) heading1 -= 360;
		if (heading2 > 180) heading2 -= 360;

		averageHeading = (heading1 + heading2)/2;
		error = degrees - averageHeading;
		errorRate = error - prevError;
		steadyStateError += error;
		// using angular velocity instead of linear velocity
		velocity = kPt*error + kDt*errorRate + kIt*steadyStateError;

		// if degrees is positive, turn right
		if (degrees > 0) {
			left_drive = velocity;
			right_drive = -velocity;
		// if degrees is negative, turn right
		} else {
			left_drive = -velocity;
			right_drive = velocity;
		}

		printf("%f,%f,%f,%f\n", averageHeading, error, errorRate, velocity);
		pros::lcd::print(0,"error: %f", averageHeading);
		pros::lcd::print(2, "error rate: %f", errorRate);
		pros::lcd::print(3, "steadyStateError: %f", steadyStateError);
		pros::lcd::print(5, "velocity: %f", velocity);

		prevError = error;
		pros::delay(20);
	}
	left_drive = 0;
	right_drive = 0;
}

void skillsAuton(){
	mtr_flywheel = -127;
	pros::delay(90000);
	mtr_flywheel = 0;
}

void closeAuton(){
//goal is to score 2 triballs and touch elevation bar


}

void farAuton(){
//goal is to score 5 triballs: 1 preload 1 matchload 3 field triballs and touch elevation bar


}