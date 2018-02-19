#include "../include/main.h"

void opCtrl() {
  drive::teleop::arcade(joystick::analog(1), joystick::analog(2));
  arm::teleop();
  delay(20);
}


TaskHandle opctrl;
void operatorControl() {
  opctrl = taskRunLoop(opCtrl, 50);
}
