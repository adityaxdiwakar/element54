#include "main.h"

/**
 * Drive Program to change direction and speed
 **/

void driveSpeed(int power) {
    setMotor(CHASSIS_L1, -power);
    setMotor(CHASSIS_L2, power);
    setMotor(CHASSIS_R2, power);
    setMotor(CHASSIS_R1, -power);
}

/**
* Default to turn right w/ 127
**/

void driveTurn(int power) {
    setMotor(CHASSIS_L1, -power);
    setMotor(CHASSIS_L2, power);
    setMotor(CHASSIS_R2, -power);
    setMotor(CHASSIS_R1, power);
}

void driveForward() {
  driveSpeed(127);
}

void driveBackward() {
  driveSpeed(-127);
}

void driveLeft() {
  driveTurn(-127);
}

/**
 * Arm Program to calculate current position and modify
 * values to get to new position using while loops
 **/

void armTo(void *armPos) {
  int target = (int)armPos;
  int current = analogRead(ARM_SENSOR);
  while(target > current || target < current) {
    int current = analogRead(ARM_SENSOR);
    if(current < target - 5) {
      arm(127);
    }
    if(current > target + 5) {
      arm(-127);
    }
    else {
      arm(0);
    }
  }
  arm(0);
}

void armUp(void *armPos) {
  int target = (int)armPos;
  int current = analogRead(ARM_SENSOR);
  while(current < target) {
    if(current < target) {
      delay(5);
  }
    else {
      arm(0);
    }
}
}

void armDown(void *armPos) {
  while(true) {
    arm(-127);
  }
}

void barDown(void *barPos) {
  int target = (int)barPos;
  int current = analogRead(BAR_SENSOR);
  while(current < target) {
    if(current < target) {
      delay(5);
  }
    else {
      bar(0);
    }
}
}

/**
 * Bar Program to calculate current position and modify
 * values to get to a new position using while loops
 **/

void barTo(void *barPos) {
  int start = 0;
  int target = (int)barPos;
  int current = analogRead(BAR_SENSOR);
  while((target > current + 5 || target < current -5) && start == 0 && isEnabled()) {
    int current = analogRead(BAR_SENSOR);
    if(target > current + 5) {
      bar(-127);
    }
    if(target < current - 5) {
      bar(127);
    }
    else {
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
 * Simple program designed to start the robot with the
 * roller intake in the intake position during autonomous controls
 * Insert this in the front of most controls and continue to test
 * with random weights and batteries
 **/

void startupSequence() {
    TaskHandle pidRoller_1 = taskRunLoop(rollerPID, 50);
    wait(100);
    int barPos = 400;
    TaskHandle moveBar_1 = taskCreate(barTo, TASK_DEFAULT_STACK_SIZE, (void*)barPos, TASK_PRIORITY_DEFAULT);
    while(analogRead(BAR_SENSOR) > 400) {
      delay(10);
    }
    bar(0);
    taskDelete(moveBar_1);
}

/**
 * Based on values, going backward is negative and positive is forward
 **/

void
driveTo(void* basePos) {
  int target = (int)basePos;
  int current = encoderGet(ENC_RIGHT);
  while(current < target - 5 || current > target + 5) {
    if(current < target) {
      driveSpeed(127);
    }
    if(current > target) {
      driveSpeed(-127);
    }
    else driveSpeed(0);
  }
  driveSpeed(0);
}

void
driveToPID(void* basePos) {
  while(isEnabled()) {
    driveSpeed(iDrivePID((int)basePos));
  }
}

void
rotateToPID(void* gyroPos) {
  while(isEnabled()) {
    int value = iRotatePID((int)gyroPos);
    driveTurn(-value);
  }
}

void
driveForward_task(void *basePos) {
  int target = (int)basePos;
  int current = encoderGet(ENC_RIGHT);
  while(current < target) {
    if(current < target) {
      delay(5);
  }
    else {
      driveSpeed(0);
    }
}
}

void
driveBackward_task(void *basePos) {
  int target = (int)basePos;
  int current = encoderGet(ENC_RIGHT);
  while(current > target) {
    if(current > target) {
      delay(5);
  }
    else {
      driveSpeed(0);
    }
}
}


void
mogoDown_task(void *mogoPos) {
  int target = (int)mogoPos;
  int current = analogRead(MOGO_SENSOR);
  while(current < target) {
    if(current < target) {
      delay(5);
    }
    else {
      mogo(0);
    }
  }
}

void pickUp() {
  rollerIN();
  wait(250);
  arm(-127);
  while(analogRead(ARM_SENSOR) > 1700) {
    setMotor(ROLL_LR1, -127);
    delay(15);
  }
  arm(0); wait(100); rollerPID();
}


void stackCones() {
  int heights[10] = {1460, 1525, 1625, 1700, 1775, 1850, 1925, 2000, 2075, 2150};
  rollerIN();
  while(analogRead(ARM_SENSOR) > heights[0]) {
    arm(-127); }
  wait(500);
  arm(0);
  wait(150);
  wait(500);
  bar(0);  
  rollerOUT();
  wait(333);

  wait(1000);

  while(analogRead(BAR_SENSOR) > 400) {
    bar(127); }
  rollerIN();
  wait(333);
  bar(0);
  while(analogRead(ARM_SENSOR) < heights[1]) {
    arm(127);
  }
  arm(0);
  wait(150);
  bar(-127);
  wait(500);
  bar(0);  
  rollerOUT();
  wait(333);

  wait(1000);

  while(analogRead(BAR_SENSOR) > 400) {
    bar(127); }
  rollerIN();
  wait(333);
  bar(0);
  rollerIN(); 
  while(analogRead(ARM_SENSOR) > heights[0]) {
    arm(-127); }
  bar(127);
  wait(500);
  arm(0);//
  wait(150);
  while(analogRead(ARM_SENSOR) < heights[2]) {
    arm(127); }
  arm(0);
  wait(150);
  bar(-127);
  wait(500);
  bar(0);  
  rollerOUT();
  wait(333); 

  wait(1000);

   while(analogRead(BAR_SENSOR) > 400) {
    bar(127); }
  rollerIN();
  wait(333);
  bar(0);
  rollerIN(); 
  while(analogRead(ARM_SENSOR) > heights[0]) {
    arm(-127); }
  bar(127);
  wait(500);
  arm(0);//
  wait(150);
  while(analogRead(ARM_SENSOR) < heights[3]) {
    arm(127); } 
  arm(0);
  wait(150);
  bar(-127);
  wait(500);
  bar(0);  
  rollerOUT();
  wait(333);
  
  }
