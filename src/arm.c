#include "MotorDef.h"
#include "API.H"
#include "misc.h"
#include "arm.h"

// Dumper Basic Set
void SetDumper (signed char pwr)
{
    motorSet(Arm_L0,pwr);
    motorSet(Arm_R0,pwr);
    motorSet(Arm_L1,pwr = -pwr);
    motorSet(Arm_R1,pwr);
};



// Dumper Step, Non-Recording
void Dumper ()
{
    if (joystickGetDigital(1,6,JOY_UP)) SetDumper(127);
    else if(joystickGetDigital(1,6,JOY_DOWN))
    {
      if(digitalRead(DownBumpP) == 1)  SetDumper(-127);
    }
    else if(joystickGetDigital(1,6,JOY_DOWN) == 0 && joystickGetDigital(1,6,JOY_UP) == 0 && analogRead(ArmPot) > 737 && analogRead(ArmPot) < 1400) SetDumper(20);
    else if(analogRead(ArmPot) > 1400) SetDumper(0);
    else if(analogRead(ArmPot) < 737) SetDumper(0);

};

// Dumper Step w/ Recording
#include "recording.h"
#include "PreferredPronouns.h"
volatile signed char DumperPower_Prev;
void Dumper_Record ()
{
    signed char DumperPower;
    if (joystickGetDigital(1,6,JOY_UP)) DumperPower = 127;
    else if(joystickGetDigital(1,6,JOY_DOWN))
    {
      if(digitalRead(DownBumpP) == 1) DumperPower = -127;
    }
    else if(joystickGetDigital(1,6,JOY_DOWN) == 0 && joystickGetDigital(1,6,JOY_UP) == 0 && analogRead(ArmPot) > 737 && analogRead(ArmPot) < 1400) DumperPower = 20;
    else if(analogRead(ArmPot) > 1400) DumperPower = 0;
    else if(analogRead(ArmPot) < 737) DumperPower = 0;
    SetDumper(DumperPower);
    if (DumperPower != DumperPower_Prev)
        RecordInstruction(Label_Dumper,DumperPower_Prev = DumperPower);
};
