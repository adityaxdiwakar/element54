#include "main.h"

void
initializeIO( ) {
  setupMotor(CHASSIS_R2, true, false);
  setupMotor(CHASSIS_R1, false, false);
  setupMotor(MOGO_L1, false, false);
  setupMotor(MOGO_R1, false, false);
  setupMotor(ARM_L1, false, true);
  setupMotor(ARM_R1, true, true);
  setupMotor(CHAIN_LR1, true, false); //mini-4-bar, currently not renamed for time
  setupMotor(ROLL_LR1, false, false);
  setupMotor(CHASSIS_L1, true, true);
  setupMotor(CHASSIS_L2, false, false);
}

void
initialize() {
  ENC_RIGHT = encoderInit(ENC_RT, ENC_RB, true);
  GYRO_LR1 = gyroInit(GYRO, 0);
  lcdInit(uart1);
  lcdClear(uart1);

  if(!isEnabled()) { 
  lcdAuton(); }
}