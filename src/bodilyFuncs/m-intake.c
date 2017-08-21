#include "intake.h"
#include "API.h"
#include "MotorDef.h"

// Intake Basic Set
void SetIntakeA (signed char pwr)
{
  motorSet(MobileY, pwr);
};

//https://www.youtube.com/watch?v=h9vMpX_uVA0
// Intake Step, Non-Recording
void IntakeA ()
{
  if (joystickGetDigital(1,8,JOY_UP)) SetIntakeA(127);
  else if (joystickGetDigital(1,8,JOY_DOWN)) SetIntakeA(-127);
  else SetIntakeA(0);
}

// Intake Step w/ Recording
#include "recording.h"
#include "PreferredPronouns.h"
volatile signed char IntakePowerA_Prev;
void Intake_Record ()
{
    signed char IntakePowerA;
    if (joystickGetDigital(1,8,JOY_UP)) IntakePowerA = 127;
    else if (joystickGetDigital(1,8,JOY_DOWN)) IntakePowerA = -127;
    else IntakePowerA = 0;

    SetIntakeA(IntakePowerA);
    if (IntakePowerA != IntakePowerA_Prev) RecordInstruction(Label_IntakeA,IntakePowerA_Prev = IntakePowerA);
};
