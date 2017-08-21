#include "API.H"
#include "MotorDef.h"
#include "arm.h"
#include "armvar.h"
#include "misc.h"

// Arm Basic Set
void SetArm(signed char pwr) {
  motorSet(ArmL, pwr);
  motorSet(ArmR, pwr);
 }

// Arm Step, Non-Recording
void Arm() {
  if (joystickGetDigital(1, 6, JOY_UP)) {
    SetArm(127); }
  else if (joystickGetDigital(1,6,JOY_DOWN)) {
    SetArm(-127); }
  else {
    SetArm(0); }
}

// Arm Step w/ Recording
#include "PreferredPronouns.h"
#include "recording.h"
volatile signed char ArmPower_Prev;
void Arm_Record() {
  signed char ArmPower;
  if (joystickGetDigital(1, 6, JOY_UP)) {
    ArmPower = 127;}
  else if (joystickGetDigital(1, 6, JOY_DOWN)) {
    ArmPower = -127; }
  else {
    ArmPower = 0; }

  SetArm(ArmPower);
  if (ArmPower != ArmPower_Prev)
    RecordInstruction(Label_Arm, ArmPower_Prev = ArmPower);
};
