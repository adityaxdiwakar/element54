#pragma once

void SetArm (signed char pwr);
void CheckArm ();
void Arm ();
void Arm_Record ();

extern int AvgArm;
int scaler = 0;
int armloc_prev;
