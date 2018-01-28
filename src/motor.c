// Include function prototypes
#include "main.h"

/**
 * Ports 1 and 10 linear rpm remapped values
 */
 int L298[128] = {
 	0, 0, 0, 0, 0, 0, 0, 0,
 	0, 0, 0, 0, 0, 0, 0, 11, 11, 12,
 	12, 12, 12, 13, 13, 13, 14, 14, 14, 14,
 	15, 15, 15, 16, 16, 16, 17, 17, 17, 18,
 	18, 18, 19, 19, 19, 20, 20, 20, 21, 21,
 	22, 22, 23, 23, 23, 24, 25, 25, 26, 26,
 	26, 27, 27, 28, 28, 29, 29, 30, 30, 31,
 	31, 32, 32, 33, 33, 34, 35, 35, 35, 35,
 	35, 35, 38, 38, 39, 41, 41, 41, 42, 43,
 	45, 46, 47, 47, 48, 49, 49, 50, 51, 52,
 	53, 54, 55, 56, 58, 59, 63, 66, 67, 70,
 	73, 74, 75, 78, 80, 84, 87, 88, 92, 95,
 	97, 100, 105, 108, 114, 117, 121, 122, 124, 127
 };

/**
 * Port 2-9 linear rpm remapped values
 */
int MC29[ 128 ] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 13, 13, 14,
	14, 14, 14, 15, 15, 15, 15, 16, 16, 16,
	16, 16, 17, 17, 17, 17, 17, 17, 17, 17,
	18, 18, 18, 18, 18, 18, 18, 19, 19, 19,
	19, 19, 20, 20, 20, 20, 21, 21, 21, 22,
	22, 22, 22, 23, 23, 23, 23, 24, 24, 24,
	25, 25, 25, 26, 26, 26, 27, 27, 27, 28,
	28, 28, 29, 29, 30, 30, 30, 31, 31, 32,
	32, 33, 33, 34, 34, 35, 36, 36, 37, 37,
	38, 39, 40, 40, 41, 42, 43, 44, 45, 46,
	46, 48, 49, 50, 51, 53, 55, 56, 58, 60,
	62, 64, 67, 70, 72, 76, 79, 83, 84, 127,
};

/**
 * struct definition for motor setup
 */
enMotor port[10];

/**
 * Used for motor setup
 *
 * @param 	iPort         The motor being setup
 * @param 	biIsReversed  Finds out if the motor is reversed
 * @param   bIsTruespeed  Finds out if the motor uses truespeed
 *
 * @return	Motor setup complete+
 */
void
setupMotor( unsigned char iPort, bool bIsReversed, bool bIsTruespeed ) {
  port[iPort-1].bReverse   = bIsReversed;
  port[iPort-1].bTruespeed = bIsTruespeed;
}

/**
 * Sets the motor speed based on the configuration
 *
 * @param 	iPort  The motor being set
 * @param 	iSpeed The motor speed being set
 *
 * @return	Motor set to desired speed
 */
void
setMotor( unsigned char iPort, int iSpeed ) {
  iSpeed = port[iPort-1].bReverse == true ? -iSpeed : iSpeed;

  if(port[iPort-1].bTruespeed == true) {
    if(iPort == 1 || iPort == 10) {
      iSpeed = sgn(iSpeed) * L298[abs(clipNum(iSpeed, 127, -127))];
    }
    else {
      iSpeed = sgn(iSpeed) * MC29[abs(clipNum(iSpeed, 127, -127))];
    }
  }
  motorSet( iPort , iSpeed );
}

/**
 * Sets the motor speed to the left / right side of chassis
 *
 * @param 	iSpeedL  Sets left side of chassis
 * @param 	iSpeedR  Sets right side of chassis
 *
 * @return	Motor speed to each chassis motor
 */

void
tank( int power, int turn ) {
  setMotor(CHASSIS_L1, -power - turn);
  setMotor(CHASSIS_L2, power + turn);
  setMotor(CHASSIS_R2, power - turn);
  setMotor(CHASSIS_R1, -power + turn);
}

/**
 * Sets the motor speed to arm
 *
 * @param 	iSpeed  Sets arm speed
 *
 * @return	Motor speed to each arm motor
 */
void
arm( int iSpeed ) {
  setMotor(ARM_L1, iSpeed);
  setMotor(ARM_R1, iSpeed);
}

void
bar( int iSpeed ) {
  setMotor(CHAIN_LR1, iSpeed);
}

void
mogo(int iSpeed) {
  setMotor(MOGO_L1, iSpeed);
  setMotor(MOGO_R1, iSpeed);
}

/**
 * PID for Arm
 *
 * @param 	iDes  Target value for PID
 *
 * @return	Motor speed to get to desired value
 */

pid sArmPID;
int
iArmPID( int iDes ) {
	sArmPID.kP         = 1;
  sArmPID.kD         = 1;
	sArmPID.current    = analogRead( ARM_SENSOR );
	sArmPID.error      = iDes - sArmPID.current;
	sArmPID.derivative = sArmPID.error - sArmPID.lastError;
  sArmPID.lastError  = sArmPID.error;
	return ( (sArmPID.error * sArmPID.kP) + (sArmPID.derivative * sArmPID.kD) );
}

pid sDriveFwd;
int
iDrivePID( int target ) {
  sDriveFwd.kP = .2;
  sDriveFwd.kD = 1;
  sDriveFwd.current = encoderGet(ENC_RIGHT);
  sDriveFwd.error = target - sDriveFwd.current;
  sDriveFwd.derivative = sDriveFwd.error - sDriveFwd.lastError;
  sDriveFwd.lastError = sDriveFwd.error;
  return ( (sDriveFwd.error * sDriveFwd.kP) + (sDriveFwd.derivative *sDriveFwd.kD) + (15 * (sDriveFwd.error / abs(sDriveFwd.error) ) ) );
}

int iRotatePID( int target) {
  sRotate.kP = 10;
  sRotate.kD = 7.5;
  sRotate.kI = 0;
  sRotate.current = gyroGet(GYRO_LR1);
  sRotate.error = target - sRotate.current;
  sRotate.integral += sRotate.error;  
  sRotate.derivative = sRotate.error - sRotate.lastError;
  sRotate.lastError = sRotate.error;
  return ( (sRotate.error * sRotate.kP) + (sRotate.derivative * sRotate.kD) + (sRotate.integral * sRotate.kI) );
}
