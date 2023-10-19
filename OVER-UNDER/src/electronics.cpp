#include "electronics.h"

pros::Motor mtr_lf(1, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_lb(16, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_lbh(14, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_rf(10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_rb(9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_rbh(7, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor_Group left_drive({mtr_lf, mtr_lb, mtr_lbh});
pros::Motor_Group right_drive({mtr_rf, mtr_rb, mtr_rbh});

pros::ADIDigitalOut armLeft('A', false);
pros::ADIDigitalOut armRight('B', false);

pros::Controller master(CONTROLLER_MASTER);