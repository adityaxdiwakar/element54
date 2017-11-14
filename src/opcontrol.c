#include "main.h"

/**
 * Arm Control
 *
 * @param  bBtnUp    Boolean for button up
 * @param  bBtnDown  Boolean for button down
 *
 * @return \
 * if no button is pressed, run a PID loop to stay at last
 * position. If button is pressed, go up / down respectively.
 */

int iArmDes, iOutput;
void armControl(bool bBtnUp, bool bBtnDown) {
  if (bBtnUp || bBtnDown) {
    iOutput = bBtnUp ? 127 : (bBtnDown ? -127 : 0);
    iArmDes = analogRead(ARM_SENSOR);
  }
  else if(analogRead(ARM_SENSOR) < 1500) iOutput = -20;
  else iOutput = 15;
  arm(iOutput);
}

int cChainDes, chainOutput;
void chainControl(bool bBtnUp, bool bBtnDown) {
  if (bBtnUp || bBtnDown) {
    chainOutput = bBtnUp ? -127 : (bBtnDown ? 127 : 0);
    cChainDes = analogReadCalibrated(ARM_SENSOR);
  }
  else if (analogRead(BAR_SENSOR) > 500) chainOutput = -15;
  else chainOutput = 0;
  setMotor(CHAIN_LR1, chainOutput);
}

/**
 * Intake Control
 * @return Toggle for each system
 */

int coneOutput;
void coneIntakeControl() {
  if (joystickGetDigital(1, 7, JOY_LEFT))
    coneOutput = -127;
  else if (joystickGetDigital(1, 7, JOY_DOWN))
    coneOutput = 127;
  else if (analogRead(ARM_SENSOR) < 1800 && analogRead(BAR_SENSOR) < 350) {
    coneOutput = -127;
  }
  else coneOutput = -15;
  motorSet(ROLL_LR1, coneOutput);
}

int mogoOutput;
void mogoIntakeControl() {
  if(joystickGetDigital(1,7,JOY_UP) || joystickGetDigital(1,7,JOY_RIGHT)) {
    if (joystickGetDigital(1, 7, JOY_UP))
      mogoOutput = 127;
    else if (joystickGetDigital(1, 7, JOY_RIGHT))
      mogoOutput = -127;
  }
  else mogoOutput = 0;
  setMotor(MOGO_L1, mogoOutput);
  setMotor(MOGO_R1, mogoOutput);
}

void operatorControl() {
  lcdInit(uart1);
  encoderReset(ENC_RIGHT);
  TaskHandle coneTaskHandle = taskRunLoop(coneIntakeControl, 50);
  TaskHandle mogoTaskHandle = taskRunLoop(mogoIntakeControl, 50);
  while (isEnabled()) {
    delay(20);
    tank(joystickGetAnalog(1, 2), joystickGetAnalog(1, 1));
    armControl(joystickGetDigital(1, 6, JOY_UP), joystickGetDigital(1, 6, JOY_DOWN));
    chainControl(joystickGetDigital(1, 5, JOY_UP), joystickGetDigital(1, 5, JOY_DOWN));
    lcdSetBacklight(uart1, true);
  }
  taskDelete(mogoTaskHandle);
  taskDelete(coneTaskHandle);
}
