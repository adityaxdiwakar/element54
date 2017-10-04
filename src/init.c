#include "main.h"

void
initializeIO( ) {
  setupMotor(ARM_L1, false, false);
  setupMotor(ARM_L2, false, false);
  setupMotor(ARM_L3, false, false);
  setupMotor(CHASSIS_L1, false, true);
  setupMotor(CHASSIS_L2, false, true);
  setupMotor(CHASSIS_R2, true, true);
  setupMotor(CHASSIS_R1, true, true);
  setupMotor(ARM_R3, true, false);
  setupMotor(ARM_R2, true, false);
  setupMotor(ARM_R1, true, false);
}

void
initialize( ) {
  analogCalibrate(1);
}
