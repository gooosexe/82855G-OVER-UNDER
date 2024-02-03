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
const double kDt = 1;
const double kIt = 0;
// Smallest distance from the goal
double errorLimit = 0.05;
double errorLimitAngle = 0.5;
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
	mtr_lfh.tare_position();
	mtr_rfh.tare_position();
}

/**
 * @brief
 * Retrieves the average position of the robot.
 * @return double 
 */
double getAveragePosition() {
	//printf("%d,%d,%d,%d,%d,%d\n", mtr_lf.get_position(), mtr_lb.get_position(), mtr_lfh.get_position(), mtr_rf.get_position(), mtr_rb.get_position(), mtr_rfh.get_position());
	// get average position of all motors (excluding top motors)
	double avgMotorRot = (mtr_lf.get_position() + mtr_lb.get_position() + mtr_lfh.get_position() + mtr_rf.get_position() + mtr_rb.get_position() + mtr_rfh.get_position())/6;
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
		right_drive = 0.95*velocity;

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
void turn(double degrees) {
	imu_1.tare_heading();
	imu_2.tare_heading();
	printf("imu_1: %f\n", imu_1.get_heading());
	printf("imu_2: %f\n", imu_2.get_heading());

	steadyStateError = 0;
	error = degrees;
	prevError = error;
	double averageHeading, heading1, heading2;

	while (countCheck < 40) {
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
		
		// if degrees is positive, turn right
		if (degrees > 0) {
			left_drive = velocity;
			right_drive = -velocity;
		// if degrees is negative, turn right
		} else {
			left_drive = -velocity;
			right_drive = velocity;
		}

		printf("%f,%f,%f,%f,%f\n", averageHeading, error, errorRate, velocity, steadyStateError);
		pros::lcd::print(0,"error: %f", averageHeading);
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

void skillsAuton(){
	mtr_flywheel = -127;
	pros::delay(90000);
	mtr_flywheel = 0;
}

void closeAuton(){
	// goal is AWP
	mtr_intake.move(10);
	moveStraight(-40);
	turn(-20);
	moveStraight(24);
	pros::delay(100);
	wings.set_value(true);
	pros::delay(100);
	turn(-30);
	moveStraight(10);
	wings.set_value(false);
	turn(-25);
	moveStraight(48);
}

void farAuton() {
	// goal is to score at least 4 triballs: 1 preload 3 field triballs and maybe touch elevation b
	mtr_intake.move(20);
	mtr_intake = -127;

	moveStraight(48);
	moveStraight(-12);
	turn(-75);
	moveStraight(50);
	moveStraight(-10);
	turn(140);
	moveStraight(50);
	moveStraight(-12);
	turn(180);
	moveStraight(18);
	turn(180);
	moveStraight(30);
	moveStraight(-18);
	turn(180);
	moveStraight(48);
	turn(180);
	moveStraight(52);
	//moveStraight(-40);
	//moveStraight(40);
}

