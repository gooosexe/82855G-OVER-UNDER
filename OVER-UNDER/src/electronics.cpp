#include "electronics.h"

pros::Motor mtr_lf(15, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_lb(17, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_rf(7, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_rb(9, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_lfh(14, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_rfh(6, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_flywheel(20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);

pros::Motor_Group left_drive({mtr_lf, mtr_lb, mtr_lfh});
pros::Motor_Group right_drive({mtr_rf, mtr_rb, mtr_rfh});

pros::ADIDigitalOut wings('H', true);
pros::IMU imu(8);

pros::Controller master(CONTROLLER_MASTER);
