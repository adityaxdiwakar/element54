#include "MotorDef.h"
#include "API.H"
#include "misc.h"
#include "arm.h"

// Arm Basic Set
void SetArm (signed char pwr)
{
    motorSet(Arm_L0,pwr);
    motorSet(Arm_R0,pwr);
};



// Arm Step, Non-Recording
void Arm ()
{
    if (joystickGetDigital(1,6,JOY_UP)) SetArm(127);
    if(joystickGetDigital(1,6,JOY_DOWN)) SetArm(-127);

};

// Arm Step w/ Recording
#include "recording.h"
#include "PreferredPronouns.h"
volatile signed char ArmPower_Prev;
void Arm_Record ()
{
    signed char ArmPower;
    if (joystickGetDigital(1,6,JOY_UP)) ArmPower = 127;
    else if(joystickGetDigital(1,6,JOY_DOWN))
    {
      if(digitalRead(DownBumpP) == 1) ArmPower = -127;
    }
    else if(joystickGetDigital(1,6,JOY_DOWN) == 0 && joystickGetDigital(1,6,JOY_UP) == 0 && analogRead(ArmPot) > 737 && analogRead(ArmPot) < 1400) ArmPower = 20;
    else if(analogRead(ArmPot) > 1400) ArmPower = 0;
    else if(analogRead(ArmPot) < 737) ArmPower = 0;
    SetArm(ArmPower);
    if (ArmPower != ArmPower_Prev)
        RecordInstruction(Label_Arm,ArmPower_Prev = ArmPower);
};
