/* header guard */
#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"

/**
 * Motor names
 */

#define CHASSIS_R2 3
#define CHASSIS_R1 2
#define MOGO_LR1   4
#define ARM_L1     5
#define ARM_R1     6
#define CHAIN_LR1  7
#define PINCH_LR1  8
#define CHASSIS_L1 9
#define CHASSIS_L2 10

/**
 * Sensor used for motors
 */

 //analog
#define ARM_SENSOR   1
#define CHAIN_SENSOR 2
#define MOGO_SENSOR  3
#define PINCHER_POT  4
#define GYRO         5

//digital
#define ENC_RT 1
#define ENC_RB 2
#define ENC_LB 3
#define ENC_LT 4

/**
* Typedef for certain sensors
*/

Encoder ENC_LEFT;
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

int state1;
int state2;
int state3;

void tank(int power, int turn);

void driveForward();
void posSetMogo(void *mogoPos);
void driveRight();
void mobileGoal(int iSpeed);
void driveBackward();
void driveStop();
void driveLeft();
void pincher(int iSpeed);
void posPIDBaseBWD(void *basePID_pos);
void posPIDBaseFWD(void *basePID_pos);
void beginning_coneAuton(int armPos, int basePos);
void posSetArm(void *armPos);
void posSetBase(void *basePos);
void openPincher();
void driveCustom(int custom);
void mogoHoldDown();
void posSetTurn(void *turnRad);
void driveCustomHort();
void driveLeftPivot();
void posSetChain(void *chainPos);
void testTurn();

/**
 * Sets the motor speed to arm
 *
 * @param 	iSpeed  Sets arm speed
 *
 * @return	Motor speed to each arm motor
 */
void arm(int iSpeed);

void chain(int iSpeed);

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

/* end of header guard */
#endif
