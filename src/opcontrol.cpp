#include "../include/main.h"

Encoder encR;

void operatorControl()
{
  encR = encoderInit(ENC_LT, ENC_LB, true);
  lcdInit(uart1);
  lcdSetBacklight(uart1, true);
  while (true)
  {
    drive::teleop::arcade(joystick::analog(2), joystick::analog(1));
    arm::teleop();
    mogo::teleop();
    bar::teleop();
    rollers::teleop();
    delay(20);
    if(joystick::digital(8, joystick::Up)) {
      autonomous();
    } 
    lcdPrint(uart1, 1, "%d", sensors::gyro::get());
    lcdPrint(uart1, 2, "%d", sensors::drive::right::get());

  }
}