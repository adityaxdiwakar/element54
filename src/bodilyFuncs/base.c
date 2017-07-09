#include "API.h"
#include "MotorDef.h"
volatile float LEFT,RIGHT;

void SetBase(signed char pwr)
{
  motorSet(Base_BR, pwr); //backright
  motorSet(Base_FR, pwr); //frontright
  motorSet(Base_BL, pwr); //backleft
  motorSet(Base_FL, pwr); //frontleft
}; //not used in program

void BaseClear ()
{
    LEFT = 0;
    RIGHT = 0;
};
void BaseRotate (float pwr)
{
    LEFT += pwr;
    RIGHT += pwr;
};
void BaseForward (float pwr)
{
    LEFT -= pwr;
    RIGHT += pwr;
};
inline void Norm (float n)
{
    if (n < 0) n = -n;
    if (n > 1)
    {
        LEFT /= n;
        RIGHT /= n;
    };
};
volatile signed char left_pwr,right_pwr;
void BaseApply ()
{
    Norm(LEFT);
    Norm(RIGHT);
    left_pwr = LEFT * 127.5f;
    right_pwr = RIGHT * 127.5f;
    motorSet(Base_BR,-left_pwr);
    motorSet(Base_FR,left_pwr);
    motorSet(Base_BL,-right_pwr);
    motorSet(Base_FL,right_pwr);
};

#include "recording.h"
#include "PreferredPronouns.h"
volatile signed char LEFT_Prev,RIGHT_Prev;
void BaseApply_Record ()
{
    BaseApply();
    if (left_pwr != LEFT_Prev) RecordInstruction(Label_BaseLEFT,LEFT_Prev = left_pwr);
    if (right_pwr != RIGHT_Prev) RecordInstruction(Label_BaseRIGHT,RIGHT_Prev = right_pwr);
};
