#pragma once
#include "main.h"

extern pros::Motor mtr_lf, mtr_lb, mtr_lbh, mtr_rf, mtr_rb, mtr_rbh, mtr_intake, mtr_flywheel;
extern pros::ADIDigitalOut lwing, rwing, intake, blocker, hang;
extern pros::IMU imu_1, imu_2;

extern pros::Controller master;
extern pros::Motor_Group left_drive, right_drive;