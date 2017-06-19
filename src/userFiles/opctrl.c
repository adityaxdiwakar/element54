#include "API.h"
#include "drive.h"
#include "claw.h"
#include "arm.h"
#include "recording.h"
#include "JumperDef.h"
#include "MotorDef.h"
#include "PreferredPronouns.h"
#include "functions.h"
const float Inv255 = 1 / 127.f;
inline void RenderBase ()
{
    BaseClear();
    if(joystickGetAnalog(1,2) > 20 || joystickGetAnalog(1,2) < -20)
    {
      BaseForward(joystickGetAnalog(1,2) * Inv255);
    }
    if(joystickGetAnalog(1,1) > 20 || joystickGetAnalog(1,1) < -20)
    {
      BaseRotate(joystickGetAnalog(1,1) * Inv255);
    }
};

// Non-Recording Operator Control
inline void OpCtrlStep ()
{
    RenderBase();
    BaseApply();
    Claw();
    Arm();

}
void OpCtrl ()
{
    while (1) {
      OpCtrlStep();
      delay(10);
    }
};

// Operator Control with Recording System
inline void OpCtrlStep_Record ()
{
    RenderBase();
    BaseApply_Record();
    Claw_Record();
    Arm_Record();
};
void RobotOff ()
{
    BaseClear();
    BaseApply();
    SetArm(0);
    SetClaw(0);
};
extern volatile signed char LEFT_Prev,RIGHT_Prev;
extern volatile signed char ArmPower_Prev;
extern volatile signed char ClawPower_Prev;
void ResetPrevs ()
{
    LEFT_Prev = 0;
    RIGHT_Prev = 0;
    ArmPower_Prev = 0;
    ClawPower_Prev = 0; // Claw starts open due to pre-auton.
};
volatile unsigned short FrameTime;
Instruction* volatile instrptr;
volatile unsigned int RecordUsage;
void RecordInstruction (char label, signed char power)
{
    instrptr->time = FrameTime;
    instrptr->label = label;
    instrptr->power = power;
    instrptr++;
    RecordUsage++;
};
#define UpdateRate 100
inline void ErrorBlink ()
{
    unsigned int inputstart = millis() + 1000;
    char blink = 0;
    while (1)
    {
        digitalWrite(StatusLED,blink);
        blink = !blink;
        if (millis() > inputstart) if (joystickGetDigital(1,8,JOY_UP)) break;
        wait(100);
    };
    digitalWrite(StatusLED,1);
    wait(1000);
};
inline void ErrorMultiBlink (unsigned char nblinks)
{
    unsigned int inputstart = millis() + 1000;
    while (1)
    {
        unsigned char i = 0;
        for (unsigned char i = 0; i < nblinks; i++)
        {
            digitalWrite(StatusLED,0);
            wait(100);
            if (joystickGetDigital(1,8,JOY_UP)) break;
            digitalWrite(StatusLED,1);
            wait(100);
            if (joystickGetDigital(1,8,JOY_UP)) break;
        };
        for (i = 0; i < 5; i++)
        {
            wait(100);
            if (millis() > inputstart) if (joystickGetDigital(1,8,JOY_UP)) break;
        };
    };
    digitalWrite(StatusLED,1);
    wait(1000);
};

inline void ForceFlush (FILE* file)
{
    while (fflush(file))
    {
        digitalWrite(StatusLED,1);
        wait(10);
        digitalWrite(StatusLED,0);
        wait(10);
    };
};

void OpCtrl_Record ()
{
    WAIT_FOR_START:
    RobotOff();
    while (!joystickGetDigital(1,8,JOY_UP));
    unsigned short Duration;
    char* filename = GenFileName(&Duration);
    // Max Instructions: Allocate a buffer big enough it won't get overrun during the recording.
    // Reallocating the buffer is expensive and may cause memory fragmentation, which is why we allocate it once with a very large size.
    size_t max_instructions = (Duration / UpdateRate) * MaxInstructionsPerFrame;
    Instruction* RecordMemory = malloc(max_instructions * sizeof(Instruction));
    if (!RecordMemory) goto ALLOCMEM_FAILURE;
    instrptr = RecordMemory;
    RecordUsage = 0;
    ResetPrevs();
    int LastFrame = -1000;
    wait(1000);
    unsigned int StartTime = millis();
    while ((FrameTime = millis() - StartTime) < Duration)
    {
        if (FrameTime < LastFrame + UpdateRate)
        {
            // Don't record two frames with the same time stamp.
            // Don't update anything (except Arm check) because we can't record this fast.
            continue;
        };
        LastFrame = FrameTime;
        OpCtrlStep_Record();
        if (joystickGetDigital(1,8,JOY_UP))
        {
            RobotOff();
            free(RecordMemory);
            wait(1000);
            goto WAIT_FOR_START;
        };
    };
    RobotOff();
    digitalWrite(StatusLED,0);
    wait(1000);
    FILE* outfile = fopen(filename,"w");
    if (!outfile) goto OPENFILE_FAILURE;
    if (fwrite(&RecordUsage,sizeof(RecordUsage),1,outfile) < sizeof(RecordUsage)) goto WRITEFILE_FAILURE;
    ForceFlush(outfile);
    instrptr = RecordMemory;
    while (RecordUsage--)
    {
        if (fwrite(&(instrptr->time),sizeof(instrptr->time),1,outfile) < sizeof(instrptr->time)) goto WRITEFILE_FAILURE;
        ForceFlush(outfile);
        if (fwrite(&(instrptr->label),sizeof(instrptr->label),1,outfile) < sizeof(instrptr->label)) goto WRITEFILE_FAILURE;
        ForceFlush(outfile);
        if (fwrite(&(instrptr->power),sizeof(instrptr->power),1,outfile) < sizeof(instrptr->power)) goto WRITEFILE_FAILURE;
        ForceFlush(outfile);
        instrptr++;
    };
    free(RecordMemory);
    fclose(outfile);
    digitalWrite(StatusLED,1);
    goto WAIT_FOR_START;

    WRITEFILE_FAILURE:
    fclose(outfile);
    free(RecordMemory);
    ErrorBlink();

    OPENFILE_FAILURE:
    free(RecordMemory);
    ErrorMultiBlink(2);

    ALLOCMEM_FAILURE:
    ErrorMultiBlink(3);
  };
