#pragma once
#include "main.h"

extern pros::Motor mtr_lf, mtr_lb, mtr_lbh, mtr_rf, mtr_rb, mtr_rbh, mtr_arm;
extern pros::ADIDigitalOut armLeft, armRight, armLeftIn, armRightIn;

extern pros::Controller master;
extern pros::Motor_Group left_drive, right_drive;