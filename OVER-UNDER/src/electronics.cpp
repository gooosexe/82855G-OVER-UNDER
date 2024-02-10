#include "electronics.h"

pros::Motor mtr_lf(11, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_lb(18, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_rf(1, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_rb(8, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_lbh(4, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_rbh(10, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_intake(3, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor mtr_flywheel(20, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_ROTATIONS);

pros::Motor_Group left_drive({mtr_lf, mtr_lb, mtr_lbh});
pros::Motor_Group right_drive({mtr_rf, mtr_rb, mtr_rbh});

pros::ADIDigitalOut wings('H', false);
pros::ADIDigitalOut blocker('A', false);

pros::IMU imu_1(2);
pros::IMU imu_2(7);

pros::Controller master(CONTROLLER_MASTER);
