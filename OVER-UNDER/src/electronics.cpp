#include "electronics.h"

pros::Motor mtr_lf(1);
pros::Motor mtr_lb(2);
pros::Motor mtr_rf(3);
pros::Motor mtr_rb(4);

pros::Motor_Group left_drive({mtr_lf, mtr_lb});
pros::Motor_Group right_drive({mtr_rf, mtr_rb});

pros::Controller master(CONTROLLER_MASTER);