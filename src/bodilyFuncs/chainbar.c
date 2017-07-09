#include "chainbar.h"
#include "API.h"
#include "MotorDef.h"

// Intake Basic Set
void SetChain (signed char pwr)
{
  motorSet(ChainY, pwr);
};

// Intake Step, Non-Recording
void Chain ()
{
  if (joystickGetDigital(1,5,JOY_UP)) SetChain(127);
  else if (joystickGetDigital(1,5,JOY_DOWN)) SetChain(-127);
  else SetChain(0);
}

// Intake Step w/ Recording
#include "recording.h"
#include "PreferredPronouns.h"
volatile signed char ChainPower_Prev;
void Chain_Record ()
{
    signed char ChainPower;
    if (joystickGetDigital(1,8,JOY_UP)) ChainPower = 127;
    else if (joystickGetDigital(1,8,JOY_DOWN)) ChainPower = -127;
    else ChainPower = 0;

    SetChain(ChainPower);
    if (ChainPower != ChainPower_Prev) RecordInstruction(Label_Chain,ChainPower_Prev = ChainPower);
};
