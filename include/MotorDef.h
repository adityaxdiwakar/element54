/******Motor Config*********
Base Motors -
 \ - Front Left (9)
 / - Back Left (10)
 \ - Front Right (2)
 / - Back Right (1)
Pincher - 6 (single motor)
Mogo - 5 (Y-cable)
Chainbar - 4 (Y-cable)
Arm - 3 (Y-cable)
******Motor Config*********/


#pragma once
#include <API.h>

//Sensor Configuration
Gyro gyro1;
Encoder enc1;
Encoder enc2;

//Base Motors
#define Base_BR 1
#define Base_FR 2
#define Base_BL 10
#define Base_FL 9

//Y-Cables and Singles
#define ArmL 5
#define ArmR 6
#define ChainY 7
#define MobileY 4
#define Pincher 8

// Scaling Information
#define BaseMotorTypeScale 392
#define TorqueMotorEncoderScale 627.2

//Global Vars
#define Page_Num 50
