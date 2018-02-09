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
void armControl(bool bBtnUp, bool bBtnDown, bool bBtn2Up, bool bBtn2Down)
{
  if (bBtnUp || bBtnDown || bBtn2Up || bBtn2Down)
  {
    if(bBtnUp || bBtn2Up) iOutput = 127;
    else if(bBtnDown || bBtn2Down) iOutput = -127;
    else iOutput = 0;
  }
  else if (analogRead(ARM_SENSOR) < 1500)
    iOutput = -20;
  else
    iOutput = 15;
  arm(iOutput);
}

int cChainDes, chainOutput;
void chainControl(bool bBtnUp, bool bBtnDown, bool bBtn2Up, bool bBtn2Down)
{
  if (bBtnUp || bBtnDown || bBtn2Up || bBtn2Down)
  {
    if(bBtnUp || bBtn2Up) chainOutput = -127;
    else if(bBtnDown || bBtn2Down) chainOutput = 127;
    else chainOutput = 0;
  }
  else if (analogRead(BAR_SENSOR) > 30)
    chainOutput = -15;
  else
    chainOutput = 15;
  setMotor(CHAIN_LR1, chainOutput);
}

/**
 * Intake Control
 * @return Toggle for each system
 */

int state;
int coneOutput;
void coneIntakeControl()
{
  while (isEnabled())
  {
    if (joystickGetDigital(1, 7, JOY_DOWN) || joystickGetDigital(2,7,JOY_DOWN))
    {
      setMotor(ROLL_LR1, 127);
      for (int i = 0; i < 25; i++)
      {
        setMotor(ROLL_LR1, 127);
        delay(10);
  if (joystickGetDigital(1, 7, JOY_LEFT) || joystickGetDigital(2,7,JOY_LEFT))
        {
          i = 101;
        }
      }
    }
    else if (joystickGetDigital(1, 7, JOY_LEFT) || joystickGetDigital(2,7,JOY_LEFT))
    {
    coneOutput = -127;
    }
    else if (analogRead(ARM_SENSOR) < 1800 && analogRead(BAR_SENSOR) < 25) {
      coneOutput = -127;
    }
    else
      coneOutput = -12;

    setMotor(ROLL_LR1, coneOutput); //up should push
  }
}

int mogoOutput;
void mogoIntakeControl()
{
  if (joystickGetDigital(1, 7, JOY_UP) || joystickGetDigital(1, 7, JOY_RIGHT) || joystickGetDigital(2, 7, JOY_UP) || joystickGetDigital(2, 7, JOY_RIGHT))
  {
    if (joystickGetDigital(1, 7, JOY_UP) || joystickGetDigital(2, 7, JOY_UP))
      mogoOutput = 127;
    else if (joystickGetDigital(1, 7, JOY_RIGHT) || joystickGetDigital(2, 7, JOY_RIGHT))
      mogoOutput = -127;
  }
  else if(analogRead(MOGO_SENSOR) > 3000) 
    mogoOutput = 30;
  else 
    mogoOutput = 0;
  setMotor(MOGO_L1, mogoOutput);
  setMotor(MOGO_R1, mogoOutput);
}

int drivePos, gyroPos;
void baseHold()
{
  bool powerMe = 0;
  while (true)
  {
    if (joystickGetDigital(1, 8, JOY_LEFT))
    {
      powerMe = 1;
      drivePos = encoderGet(ENC_RIGHT);
      gyroPos = gyroGet(GYRO_LR1);
    }
    wait(250);
    while (powerMe == 1)
    {
      if ((encoderGet(ENC_RIGHT) > drivePos + 3) || (encoderGet(ENC_RIGHT) < drivePos - 3))
      {
        driveSpeed(iDrivePID(drivePos));
      }
      if (joystickGetDigital(1, 8, JOY_LEFT))
        powerMe = 0;
    }
    wait(250);
  }
}

void operatorControl()
{
  lcdInit(uart1);
  encoderReset(ENC_RIGHT);
	TaskHandle coneTaskHandle = taskCreate(coneIntakeControl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle mogoTaskHandle = taskRunLoop(mogoIntakeControl, 50);
  while (isEnabled())
  {
    delay(20);
    tank(joystickGetAnalog(1, 2) + joystickGetAnalog(2,2), joystickGetAnalog(1, 1) + joystickGetAnalog(2, 1));
    armControl(joystickGetDigital(1, 6, JOY_UP), joystickGetDigital(1, 6, JOY_DOWN), joystickGetDigital(2,6,JOY_UP), joystickGetDigital(2,6,JOY_DOWN));
    chainControl(joystickGetDigital(1, 5, JOY_UP), joystickGetDigital(1, 5, JOY_DOWN), joystickGetDigital(2,5,JOY_UP), joystickGetDigital(2,5,JOY_DOWN));
    if (joystickGetDigital(1, 8, JOY_RIGHT))
    {
      taskSuspend(coneTaskHandle);
      taskSuspend(mogoTaskHandle);
      autonomous();
      taskResume(coneTaskHandle);
      taskResume(mogoTaskHandle);
    }
  }
  taskDelete(mogoTaskHandle);
  taskDelete(coneTaskHandle);
}
