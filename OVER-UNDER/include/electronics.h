#pragma once
#include "main.h"

extern pros::Motor mtr_lf, mtr_lb, mtr_lfh, mtr_rf, mtr_rb, mtr_rfh, mtr_arm, mtr_flywheel;
extern pros::ADIDigitalOut wings;
extern pros::IMU imu_1, imu_2;

extern pros::Controller master;
extern pros::Motor_Group left_drive, right_drive;