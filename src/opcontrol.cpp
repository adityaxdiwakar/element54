#include "../include/main.h"

void opCtrl() {
  drive::teleop::arcade(joystick::analog(1), joystick::analog(2));
  arm::teleop();
  mogo::teleop();
  rollers::teleop();
  delay(20);
}


TaskHandle opctrl;
void operatorControl() {
  while(true) { 
    opctrl = taskRunLoop(opCtrl, 50); }
}
