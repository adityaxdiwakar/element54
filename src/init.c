#include "main.h"

void
initializeIO( ) {
  setupMotor(CHASSIS_R2, false, false);
  setupMotor(CHASSIS_R1, false, false);
  setupMotor(MOGO_LR1, false, false);
  setupMotor(ARM_L1, false, true);
  setupMotor(ARM_R1, false, true);
  setupMotor(CHAIN_LR1, true, true);
  setupMotor(PINCH_LR1, false, false);
  setupMotor(CHASSIS_L1, true, true);
  setupMotor(CHASSIS_L2, true, false);
}

void
initialize() {
  analogCalibrate(ARM_SENSOR);
  analogCalibrate(CHAIN_SENSOR);
}
