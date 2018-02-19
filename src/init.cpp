#include "../include/main.h"
#include "../include/motors.h"

extern "C" {
void __libc_init_array();
}

void initializeIO() {
  __libc_init_array();
  rollers::init(ROLL_M1, false);
  arm::init(ARM_L1, false, "left");
  arm::init(ARM_R1, false, "right");
  drive::init(CHASSIS_L1, false, true, "frontLeft");
  drive::init(CHASSIS_L2, false, true, "backLeft");
  drive::init(CHASSIS_R1, false, true, "frontRight");
  drive::init(CHASSIS_R2, false, true, "backRight");
  mogo::init(MOGO_L1, false, "left");
  mogo::init(MOGO_R1, false, "right");
} 

void initialize() {


}
