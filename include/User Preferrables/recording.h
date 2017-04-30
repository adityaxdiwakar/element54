#pragma once

void RecordInstruction (char label, signed char power);
void RobotOff ();
char* GenFileName (unsigned short* duration);
typedef struct
{
    unsigned short time;
    char label;
    signed char power;
}
Instruction;
