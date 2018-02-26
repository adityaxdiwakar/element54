#include "../include/main.h"

extern "C" {
void __libc_init_array();
}

void initializeIO() {
  __libc_init_array();
} 

int gyroInitVar, encLInitVar, enCRInitVar;
void initialize() {
  rollers::init(ROLL_M1, -1);
  arm::init(ARM_L1, 1, "left");
  arm::init(ARM_R1, -1, "right");
  drive::init(CHASSIS_L1, -1, true, "frontLeft");
  drive::init(CHASSIS_L2, 1, true, "backLeft");
  drive::init(CHASSIS_R1, -1, true, "frontRight");
  drive::init(CHASSIS_R2, -1, true, "backRight");
  mogo::init(MOGO_L1, -1, "left");
  mogo::init(MOGO_R1, 1, "right");
  bar::init(BAR_M1, 1, "main");
  gyroInitVar = sensors::gyro::get();
  encLInitVar = sensors::drive::left::get();
  enCRInitVar = sensors::drive::right::get();
  }
