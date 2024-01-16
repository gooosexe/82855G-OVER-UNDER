#pragma once
extern double kP, kD, kI;
extern double errorLimit;
extern double velocity, error, steadyStateError;

void moveStraight(double distance);
void turn(double degrees);
void skillsAuton();
void closeAuton();
void farAuton();
