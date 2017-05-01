#pragma once
#include <API.h>
Gyro gyro1;
Encoder enc1; //left
Encoder enc2; //right

#define Page_Num 50

#define Arm_L0 3 // Power Exp
#define Arm_L1 2
#define Arm_R0 9 // Power Exp
#define Arm_R1 8

#define ClawLeftMotor 1
#define ClawRightMotor 10

#define BaseMotorTypeScale 392
#define TorqueMotorEncoderScale 627.2

#define Base_FL 5
#define Base_FR 7
#define Base_BL 4
#define Base_BR 6

//Sensors (Digital)
#define DownBumpP 12
#define BackLeftBUM 11
#define BackBump 10
#define BackRightBUM 9
#define Jumper //8
#define LeftTopENC 6
#define LeftBotENC 7
#define RightTopENC 4
#define RightBotENC 5
#define Jumper //4
#define Jumper
#define Jumper
#define void_port

//Sensors (Analog)
#define AutoPot 1
#define ArmPot 2
#define GYR 3
#define LeftLIN 4
#define RightLIN 5
#define ClawPot 6
