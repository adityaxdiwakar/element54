#include "intake.h"
#include "API.h"
#include "MotorDef.h"

// Intake Basic Set
void SetIntakeA (signed char state)
{
  digitalWrite(12, state);
};

void SetIntakeB (signed char state)
{
  digitalWrite(11, state);
};

// Intake Step, Non-Recording
void IntakeA ()
{
  if (joystickGetDigital(1,8,JOY_LEFT)) SetIntakeA(0);
  else if (joystickGetDigital(1,8,JOY_RIGHT)) SetIntakeA(1);
}

void IntakeB ()
{
  if (joystickGetDigital(1,7,JOY_LEFT)) SetIntakeB(0);
  else if (joystickGetDigital(1,7,JOY_RIGHT)) SetIntakeB(1);
}

// Intake Step w/ Recording
#include "recording.h"
#include "PreferredPronouns.h"
volatile signed char IntakePowerA_Prev;
volatile signed char IntakePowerB_Prev;
void Intake_Record ()
{
    signed char IntakePowerA;
    if (joystickGetDigital(1,8,JOY_LEFT)) IntakePowerA = 0;
    else if (joystickGetDigital(1,8,JOY_RIGHT)) IntakePowerA = 1;
    else IntakePowerA = 0;

    signed char IntakePowerB;
    if (joystickGetDigital(1,7,JOY_LEFT)) IntakePowerB = 0;
    else if (joystickGetDigital(1,7,JOY_RIGHT)) IntakePowerB = 1;
    else IntakePowerB = 0;

    SetIntakeA(IntakePowerA);
    SetIntakeB(IntakePowerB);
    if (IntakePowerA != IntakePowerA_Prev) RecordInstruction(Label_IntakeA,IntakePowerA_Prev = IntakePowerA);
    if (IntakePowerB != IntakePowerB_Prev) RecordInstruction(Label_IntakeB,IntakePowerB_Prev = IntakePowerB);
};
