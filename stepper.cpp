#include "stepper.h"

const int dir_pin_x = 33;
const int stp_pin_x = 34;

void stepper_setup(){
  // Creates an instance
  AccelStepper axis_x(AccelStepper::DRIVER, dir_pin_x, stp_pin_x);
}