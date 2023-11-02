#include "electronics.h"

pros::Motor mtr_lf(3, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_lb(16, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_lfh(1, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_rf(7, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_rb(17git , pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_rfh(9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor mtr_flywheel(20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor_Group left_drive({mtr_lf, mtr_lb, mtr_lfh});
pros::Motor_Group right_drive({mtr_rf, mtr_rb, mtr_rfh});

pros::ADIDigitalOut wings('A', false);

pros::Controller master(CONTROLLER_MASTER);
