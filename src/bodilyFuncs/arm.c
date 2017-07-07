#include "API.H"
#include "MotorDef.h"
#include "arm.h"
#include "misc.h"
#include "armvar.h"

// Arm Basic Set
void SetArm(signed char pwr) {
  motorSet(Arm_L0, pwr);
  motorSet(Arm_R0, pwr);
};

signed char GetArm() {
  int LAM = motorGet(Arm_L0);
  int RAM = motorGet(Arm_R0);
  int LRAM = LAM + RAM;
  int AvgArm = LRAM / 2;
  return AvgArm;
}

// Arm Step, Non-Recording
void Arm() {
  if (joystickGetDigital(1, 6, JOY_UP)) {
    SetArm(127);
    armloc_prev = 0;
  }
  if (joystickGetDigital(1, 6, JOY_DOWN)) {
    SetArm(-127);
    armloc_prev = 0; }
    else {
      SetArm(0);
    }

  }

// Arm Step w/ Recording
#include "PreferredPronouns.h"
#include "recording.h"
volatile signed char ArmPower_Prev;
void Arm_Record() {
  signed char ArmPower;
  if (joystickGetDigital(1, 6, JOY_UP))
    ArmPower = 127;
  else if (joystickGetDigital(1, 6, JOY_DOWN)) {
    if (digitalRead(DownBumpP) == 1)
      ArmPower = -127;
  } else if (joystickGetDigital(1, 6, JOY_DOWN) == 0 &&
             joystickGetDigital(1, 6, JOY_UP) == 0 &&
             analogRead(ArmPot) > 737 && analogRead(ArmPot) < 1400)
    ArmPower = 20;
  else if (analogRead(ArmPot) > 1400)
    ArmPower = 0;
  else if (analogRead(ArmPot) < 737)
    ArmPower = 0;
  SetArm(ArmPower);
  if (ArmPower != ArmPower_Prev)
    RecordInstruction(Label_Arm, ArmPower_Prev = ArmPower);
};
