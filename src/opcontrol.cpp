#include "../include/main.h"

void opCtrl() {
  drive::teleop::arcade(joystick::analog(2), joystick::analog(1));
  arm::teleop();
  mogo::teleop();
  rollers::teleop();
  bar::teleop();
  lcdPrint(uart1, 1, "A: %d, M: %d", sensors::arm::get(), sensors::mogo::get());
  lcdPrint(uart1, 2, "B: %d", sensors::bar::get());
  delay(20);
}

void operatorControl() {
  lcdSetBacklight(uart1, true);
  while(true) { 
    opCtrl();
    }
}