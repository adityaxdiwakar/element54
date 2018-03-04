#include "main.h"

int iArmDes, iOutput;
void armControl()
{
  if (joystickGetDigital(1,6,JOY_UP) || joystickGetDigital(1,6,JOY_DOWN))
  {
    if (joystickGetDigital(1,6,JOY_UP))
      iOutput = 127;
    else if (joystickGetDigital(1,6,JOY_DOWN))
      iOutput = -127;
    else
      iOutput = 0;
  }
  else if (analogRead(ARM_SENSOR) < 1500)
    iOutput = -20;
  else
    iOutput = 15;
  arm(iOutput);
}

int cChainDes, chainOutput;
void chainControl()
{
  if (joystickGetDigital(1,5,JOY_UP) || joystickGetDigital(1,5,JOY_DOWN))
  {
    if (joystickGetDigital(1,5,JOY_UP))
      chainOutput = -127;
    else if (joystickGetDigital(1,5,JOY_DOWN))
      chainOutput = 127;
    else
      chainOutput = 0;
  }
  else if (analogRead(BAR_SENSOR) > 1500)
    chainOutput = -15;
  else
    chainOutput = 15;
  setMotor(CHAIN_LR1, chainOutput);
}

int mogoOutput;
void mogoControl()
{
  if (joystickGetDigital(1, 7, JOY_UP) || joystickGetDigital(1, 7, JOY_RIGHT) || joystickGetDigital(2, 7, JOY_UP) || joystickGetDigital(2, 7, JOY_RIGHT))
  {
    if (joystickGetDigital(1, 7, JOY_UP) || joystickGetDigital(2, 7, JOY_UP))
      mogoOutput = 127;
    else if (joystickGetDigital(1, 7, JOY_RIGHT) || joystickGetDigital(2, 7, JOY_RIGHT))
      mogoOutput = -127;
  }
  else if (analogRead(MOGO_SENSOR) > 3000)
    mogoOutput = 30;
  else
    mogoOutput = 0;
  mogo(mogoOutput);
}

int rOutput, rollTime, bSpin;
void rollerControl() {
      if(joystickGetDigital(1, 7, JOY_LEFT)) {
          iOutput = -127; 
          bSpin = false;
          }
      else if(joystickGetDigital(1, 7, JOY_DOWN)) {
          iOutput = 127; 
          bSpin = true;
          rollTime = millis();
          }
      else if((millis()-rollTime < 250) && bSpin) iOutput = 127;
      else if (analogRead(ARM_SENSOR) < 1800 && analogRead(BAR_SENSOR) < 900)
          iOutput = -127;
      else
        iOutput = -18;
      setMotor(ROLL_LR1, iOutput);
}

void operatorControl()
{
  encoderReset(ENC_RIGHT);
  TaskHandle lcdController = taskCreate(lcdCounter, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  while (isEnabled()) 
  {
    delay(20);
    rollerControl();
    mogoControl();
    armControl();
    chainControl();
    tank(joystickGetAnalog(1, 2) + joystickGetAnalog(2,2), joystickGetAnalog(1, 1) + joystickGetAnalog(2, 1));
    if(joystickGetDigital(1,8,JOY_UP)) {
      progSkills();    
    }
  }
  taskDelete(lcdController);
}

