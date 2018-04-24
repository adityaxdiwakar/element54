#include "../include/main.h"

extern "C" {
void __libc_init_array();
}

void initializeIO() {
  __libc_init_array();
  rollers::init(6, -1);
  arm::init(3, -1, "left");
  arm::init(8, -1, "right");
  drive::init(2, 1, true, "frontLeft");
  drive::init(1, 1, true, "backLeft");
  drive::init(10, 1, true, "backRight");
  drive::init(9, -1, true, "frontRight");
  mogo::init(4, -1, "main");
  bar::init(5, 1, "left");
  bar::init(7, 1, "right");
  printf("%d %d", sensors::drive::left::get(), sensors::drive::right::get());
} 

void initialize() {
  lcdInit(uart1);
  //drive::joyInit.defaultY = joystick::analog(2);
  //drive::joyInit.defaultX = joystick::analog(1);
}
