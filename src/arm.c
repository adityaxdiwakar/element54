#include <MotorDef.h>
#include <API.h>
#include <arm.h>

void armSet(int speed) {
   motorSet(Arm_L1, -speed);
   motorSet(Arm_L0, speed);
   motorSet(Arm_R1, -speed);
   motorSet(Arm_R0, speed);
}
