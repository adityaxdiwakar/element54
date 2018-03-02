/* header guard */
#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"

/**
 * Motor names
 */

#define CHASSIS_R2 9
#define CHASSIS_R1 1
#define MOGO_L1    5
#define MOGO_R1    4
#define ARM_L1     8
#define ARM_R1     3
#define CHAIN_LR1  6
#define ROLL_LR1   7
#define CHASSIS_L1 10
#define CHASSIS_L2 2

/**
 * Sensor used for motors
 */

 //analog
#define ARM_SENSOR   1
#define BAR_SENSOR   2
#define MOGO_SENSOR  3
#define AUTO_SENSOR  4 /*
#define NOTHING      5 */
#define GYRO         6

//digital
#define ENC_RT 2
#define ENC_RB 1

/**
* Typedef for certain sensors
*/

Encoder ENC_RIGHT;
Gyro GYRO_LR1;

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
	float kI;
	float kD;
	float target;
	float integral;
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

int state1;
int state2;
int state3;

void tank(int power, int turn), driveSpeed(int power), driveTurn(int power);
void driveTo(void *basePos), driveForward(), driveBackward();

void driveToPID(void *basePos), rotateToPID(void *gyroPos);

/**
 * Sets the motor speed to arm
 *
 * @param 	iSpeed  Sets arm speed
 *
 * @return	Motor speed to each arm motor
 */

void arm(int iSpeed), armTo(void *armPos), armUp(void *armPos), armDown(void *armPos);

void chain(int iSpeed), bar(int iSpeed), barTo(void *barPos), barDown(void *barPos);

void mogo(int iSpeed);

void rollerPID(), rollerIN(), rollerOUT(), moveRoller(int iSpeed);

/**
 * PID for Arm
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */

int iArmPID(int iDes);

int iChainPID(int cDes);

int iDrivePID(int target);

int iRotatePID(int target);

pid sRotate;

/* end of header guard */
#endif
