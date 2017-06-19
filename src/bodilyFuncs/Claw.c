#include "claw.h"
#include "API.h"
#include "MotorDef.h"

// Claw Basic Set
void SetClaw (signed char state)
{
  digitalWrite(12, state);
};
// Claw Step, Non-Recording
void Claw ()
{
    if (joystickGetDigital(1,5,JOY_DOWN)) SetClaw(0);
    else if (joystickGetDigital(1,5,JOY_UP)) SetClaw(1);
};

// Claw Step w/ Recording
#include "recording.h"
#include "PreferredPronouns.h"
volatile signed char ClawPower_Prev;
void Claw_Record ()
{
    signed char ClawPower;
    if (joystickGetDigital(1,5,JOY_DOWN)) ClawPower = -127;
    else if (joystickGetDigital(1,5,JOY_UP)) ClawPower = 127;
    else ClawPower = 0;
    SetClaw(ClawPower);
    if (ClawPower != ClawPower_Prev) RecordInstruction(Label_Claw,ClawPower_Prev = ClawPower);
};
