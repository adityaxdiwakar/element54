#include "main.h"

/**
 * Arm Program to calculate current position and modify
 * values to get to new position using while loops
 **/

void armTo(void * armPos) {
  int target = (int) armPos;
  int current = analogRead(ARM_SENSOR);
  while (target > current || target < current) {
    int current = analogRead(ARM_SENSOR);
    if (current < target - 5) {
      arm(127);
    }
    if (current > target + 5) {
      arm(-127);
    } else {
      arm(0);
    }
  }
  arm(0);
}

void armUp(void * armPos) {
  int target = (int) armPos;
  int current = analogRead(ARM_SENSOR);
  while (current < target) {
    if (current < target) {
      delay(5);
    } else {
      arm(0);
    }
  }
}

void armDown(void * armPos) {
  while (true) {
    arm(-127);
  }
}

/**
 * Arm Functions
 **/

void barDown(void * barPos) {
  int target = (int) barPos;
  int current = analogRead(BAR_SENSOR);
  while (current < target) {
    if (current < target) {
      delay(5);
    } else {
      bar(0);
    }
  }
}

void barTo(void * barPos) {
  int start = 0;
  int target = (int) barPos;
  int current = analogRead(BAR_SENSOR);
  while ((target > current + 5 || target < current - 5) && start == 0 && isEnabled()) {
    int current = analogRead(BAR_SENSOR);
    if (target > current + 5) {
      bar(-127);
    }
    if (target < current - 5) {
      bar(127);
    } else {
      bar(0);
      start = 1;
    }
  }
}

/**
 * Roller functions found below
 **/

void rollerIN() {
  setMotor(ROLL_LR1, -127);
}

void rollerOUT() {
  setMotor(ROLL_LR1, 127);
}

void rollerPID() {
  setMotor(ROLL_LR1, -20);
}

void moveRoller(int iSpeed) {
  setMotor(ROLL_LR1, -iSpeed);
}

/**
 * Drive Values
 **/

void
driveForward() {
  driveSpeed(127);
}

void
driveBackward() {
  driveSpeed(-127);
}

void
driveSpeed(int power) {
  setMotor(CHASSIS_L1, -power);
  setMotor(CHASSIS_L2, power);
  setMotor(CHASSIS_R2, power);
  setMotor(CHASSIS_R1, -power);
}

void
driveTurn(int power) {
  setMotor(CHASSIS_L1, -power);
  setMotor(CHASSIS_L2, power);
  setMotor(CHASSIS_R2, -power);
  setMotor(CHASSIS_R1, power);
}

void
driveTo(void * basePos) {
  int target = (int) basePos;
  int current = encoderGet(ENC_RIGHT);
  while (current < target - 5 || current > target + 5) {
    if (current < target) {
      driveSpeed(127);
    }
    if (current > target) {
      driveSpeed(-127);
    } else driveSpeed(0);
  }
  driveSpeed(0);
}

void
driveToPID(void * basePos) {
  while (isEnabled()) {
    driveSpeed(iDrivePID((int) basePos));
  }
}

void
rotateToPID(void * gyroPos) {
  while (isEnabled()) {
    int value = iRotatePID((int) gyroPos);
    driveTurn(-value);
  }
}
