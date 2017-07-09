#include "API.h"
#include "MotorDef.h"
#include "pincher.h"

// Intake Basic Set
void SetPincher(signed char pwr) { motorSet(Pincher, pwr); };

// Intake Step, Non-Recording
void Pinch () {
  if (joystickGetDigital(1, 7, JOY_UP))
    SetPincher(127);
  else if (joystickGetDigital(1, 7, JOY_DOWN))
    SetPincher(-127);
  else
    SetPincher(0);
}

// Intake Step w/ Recording
#include "PreferredPronouns.h"
#include "recording.h"
volatile signed char PinchPower_Prev;
void Pinch_Record() {
  signed char PinchPower;
  if (joystickGetDigital(1, 8, JOY_UP))
    PinchPower = 127;
  else if (joystickGetDigital(1, 8, JOY_DOWN))
    PinchPower = -127;
  else
    PinchPower = 0;

  SetPincher(PinchPower);
  if (PinchPower != PinchPower_Prev)
    RecordInstruction(Label_Pinch, PinchPower_Prev = PinchPower);
};
