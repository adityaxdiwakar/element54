/* header guard */
#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"

/**
 * Motor names
 */
#define ARM_L1     1
#define ARM_L2     2
#define ARM_L3     3
#define CHASSIS_L1 4
#define CHASSIS_L2 5
#define CHASSIS_R2 6
#define CHASSIS_R1 7
#define ARM_R3     8
#define ARM_R2     9
#define ARM_R1     10

/**
 * Sensor used for motors
 */
#define ARM_SENSOR 1

/**
 * Struct for motor seutp
 *
 * @param  bReverse    Sets inverted power to motor
 * @param  bTruespeed  Sets linear RPM curve to motor
 */
typedef struct _motor{
  bool bReverse;
  bool bTruespeed;
}enMotor;

/**
 * Struct for easy PID
 *
 * @param  current     Current position
 * @param  kP          Constant proportional term
 * @param  KD          Constant derivative term
 * @param  target      Target position
 * @param  error       Target (-) Current
 * @param  derivative  Predicts future trends in the error
 * @param  lastError   Last error... its in the name <3
 */
typedef struct {
	float current;
	float kP;
	float kD;
	float target;
	float error;
	float derivative;
	float lastError;
} pid;

/**
 * Used for motor setup
 *
 * @param 	iPort         The motor being setup
 * @param 	biIsReversed  Finds out if the motor is reversed
 * @param   bIsTruespeed  Finds out if the motor uses truespeed
 *
 * @return	Motor setup complete+
 */
void setupMotor(unsigned char eMotor, bool bIsReversed, bool bIsTruespeed);

/**
 * Sets the motor speed based on the configuration
 *
 * @param 	iPort  The motor being set
 * @param 	iSpeed The motor speed being set
 *
 * @return	Motor set to desired speed
 */
void setMotor(unsigned char eMotor, int iSpeed);

/**
 * Sets the motor speed to the left / right side of chassis
 *
 * @param 	iSpeedL  Sets left side of chassis
 * @param 	iSpeedR  Sets right side of chassis
 *
 * @return	Motor speed to each chassis motor
 */
void tank(int iSpeedL, int iSpeedR);

/**
 * Sets the motor speed to arm
 *
 * @param 	iSpeed  Sets arm speed
 *
 * @return	Motor speed to each arm motor
 */
void arm(int iSpeed);

/**
 * PID for Arm
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */
int iArmPID(int iDes);

/* end of header guard */
#endif
