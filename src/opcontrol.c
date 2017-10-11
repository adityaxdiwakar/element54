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
  } else if (analogRead(ARM_SENSOR) < 650) {
    iOutput = -15;
  } else {
    iOutput = 15;
  }
  arm(iOutput);
}

int cChainDes, chainOutput;
void chainControl(bool bBtnUp, bool bBtnDown) {
  if (bBtnUp || bBtnDown) {
    chainOutput = bBtnUp ? 127 : (bBtnDown ? -127 : 0);
    cChainDes = analogReadCalibrated(ARM_SENSOR);
  } else
    chainOutput = 0;
  chain(chainOutput);
}

/**
 * Intake Control
 * @return Toggle for each system
 */

int coneOutput;
void coneIntakeControl() {
  if (joystickGetDigital(1, 7, JOY_LEFT))
    coneOutput = 127;
  else if (joystickGetDigital(1, 7, JOY_DOWN))
    coneOutput = -127;
  else
    coneOutput = 0;
  motorSet(PINCH_LR1, coneOutput);
}

int mogoOutput;
void mogoIntakeControl() {
  if (joystickGetDigital(1, 7, JOY_UP))
    mogoOutput = 127;
  else if (joystickGetDigital(1, 7, JOY_RIGHT))
    mogoOutput = -127;
  else
    mogoOutput = 0;
  setMotor(MOGO_LR1, mogoOutput);
}

void operatorControl() {
  lcdInit(uart1);
  TaskHandle coneTaskHandle = taskRunLoop(coneIntakeControl, 50);
  TaskHandle mogoTaskHandle = taskRunLoop(mogoIntakeControl, 50);
  while (isEnabled()) {
    tank(joystickGetAnalog(1, 2), joystickGetAnalog(1, 1));
    armControl(joystickGetDigital(1, 6, JOY_UP),
               joystickGetDigital(1, 6, JOY_DOWN));
    chainControl(joystickGetDigital(1, 5, JOY_UP),
                 joystickGetDigital(1, 5, JOY_DOWN));
    delay(20);
    lcdSetBacklight(uart1, true);
    lcdPrint(uart1, 1, "L:%d M:%d", encoderGet(ENC_LEFT), analogRead(MOGO_SENSOR));
		lcdPrint(uart1, 2, "A:%d G:%d", analogRead(ARM_SENSOR), analogRead(MOGO_SENSOR))/*gyroGet(GYRO_LR1))*/;
    if (joystickGetDigital(1, 8, JOY_RIGHT)) {
      encoderReset(ENC_LEFT); encoderReset(ENC_RIGHT); gyroReset(GYRO_LR1);
    }
    if(joystickGetDigital(1, 8, JOY_UP)) {
      mogoAuton();
    }
    if (joystickGetDigital(1, 8, JOY_LEFT)) {
      //mogoAuton();
      while(true) {
        driveLeftPivot();
        if(joystickGetDigital(1, 8, JOY_DOWN)) {
          break;
        }
      }
    }
  }
  taskDelete(coneTaskHandle);
  taskDelete(mogoTaskHandle);
}
