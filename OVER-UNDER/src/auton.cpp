#include "electronics.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstdio>

#define M_PI 3.14159265358979323846 

// PID constants
const double kP = 0;
const double kD = 0;
const double kI = 0;
// Smallest distance from the goal
double errorLimit = 0.001;
// PID Variables
// velocity in inches per second

double velocity, error, steadyStateError;

std::fstream posDataCSV;

/**
 * @brief
 * Retrieves the average position of the robot.
 * @return double 
 */
double getAveragePosition() {
	// get average position of all motors (excluding top motors)
	double avgMotorRot = (mtr_lf.get_position() + mtr_lb.get_position() + mtr_rf.get_position() + mtr_rb.get_position())/4;	
	return 3.25*M_PI*avgMotorRot*(5/3);
}

/**
 * @brief 
 * Records some useful metrics into a CSV file.
 */
void recordData() {
	posDataCSV.open("posData.csv", std::ios::out | std::ios::app);
	posDataCSV << error << "," << velocity << "," << steadyStateError << "\n";
	posDataCSV.close();
}

/**
 * @brief 
 * Moves the bot in a straight line.
 * @param distance in inches
 */
void moveStraight(double distance) {
	int cycles;
	steadyStateError = 0;
	error = distance;
	while (error > errorLimit) {
		cycles++;
		// distance subtracted by the average of the four ground motors
		error = distance - getAveragePosition();
		steadyStateError += error;
		velocity = kP*error + kD*(-velocity) + kI*steadyStateError;
		if (velocity < 0.01) velocity = 0;

		left_drive = velocity;
		right_drive = velocity;
		if (cycles % 10 == 0) recordData();
		pros::lcd::print(1, "error: %f", error);
		pros::lcd::print(2, "velocity: %f", velocity);
		pros::lcd::print(3, "steadyStateError: %f", steadyStateError);
		pros::delay(5);
	}	
}

/**
 * @brief 
 * Turns the bot in place.
 * @param degrees self explanatory
 */
void turn(double degrees) {
	imu.tare_heading();
	steadyStateError = 0;
	// makes sure that the degrees is between -180 and 180
	if (degrees > 180) degrees -= 360;

	while (error > errorLimit) {
		// distance subtracted by the average of the four ground motors
		error = degrees - imu.get_heading();

		steadyStateError += error;
		// using angular velocity instead of linear velocity
		velocity = kP*error + kD*(-velocity) + kI*steadyStateError;
		if (velocity < 0.01) velocity = 0;

		// if degrees is positive, turn left
		if (degrees > 0) {
			left_drive = -velocity;
			right_drive = velocity;
		// if degrees is negative, turn right
		} else {
			left_drive = velocity;
			right_drive = -velocity;
		}

		pros::lcd::print(1, "error: %f", error);
		pros::lcd::print(2, "velocity: %f", velocity);
		pros::lcd::print(3, "steadyStateError: %f", steadyStateError);
	}
}

