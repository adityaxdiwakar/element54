#include "main.h"

inline void
mogoAutonMaster() {
  encoderReset(ENC_RIGHT);

  int armPos = 2000;
  int mogoPos = 3000;
  int drivePos = 1250;
  int barPos = 350;
  setMotor(ROLL_LR1, -63);
  arm(127);
  TaskHandle barMove_1 = taskCreate(barDown, TASK_DEFAULT_STACK_SIZE, (void * ) barPos, TASK_PRIORITY_DEFAULT);
  TaskHandle armMove_1 = taskCreate(armUp, TASK_DEFAULT_STACK_SIZE, (void * ) armPos, TASK_PRIORITY_DEFAULT);
  while (analogRead(ARM_SENSOR) < armPos) {
    delay(15);
  }
  arm(0);
  mogo(127);
  while (analogRead(MOGO_SENSOR) < mogoPos) {
    delay(15);
  }
  mogo(63);
  driveSpeed(127);
  while (encoderGet(ENC_RIGHT) < 1250) {
    delay(15);
  }
  driveSpeed(0);
  encoderReset(ENC_RIGHT);
  mogoPos = 1500;
  drivePos = -1200;
  bar(127);
  mogo(-127);
  while (analogRead(MOGO_SENSOR) > 1700) {
    delay(15);
  }
  mogo(0);
  bar(0);
  armPos = 1575;
  arm(-127);
  bar(63);
  TaskHandle armMove_2 = taskCreate(armDown, TASK_DEFAULT_STACK_SIZE, (void * ) armPos, TASK_PRIORITY_DEFAULT);
  int current = 2000;
  while (current > armPos) {
    delay(15);
    arm(-127);
    if (analogRead(ARM_SENSOR) < 1000) {
      current = current;
    } else {
      current = analogRead(ARM_SENSOR);
    }
  }
  fuckme = analogRead(ARM_SENSOR);
  taskDelete(armMove_2);
  arm(0);
  bar(0);
  wait(100);
  arm(127);
  wait(50);
  arm(0);
  bar(-127);
  wait(750);
  rollerOUT();
  wait(250);
  bar(0);
  setMotor(ROLL_LR1, 0);
  arm(0);
  driveForward();
  wait(350);
  driveSpeed(0);
  bar(127);
  wait(500);
  bar(45);
  rollerIN();
  arm(-127);
  wait(500);
  arm(0);
  bar(0);
  arm(127);
  wait(150);
  arm(0);  
  TaskHandle basePID_1 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void*)drivePos, TASK_PRIORITY_DEFAULT);
  int runCone = 0;
  while (encoderGet(ENC_RIGHT) > drivePos || runCone == 0) {
    delay(15);
    if(runCone == 0) {
      bar(-127);
      wait(750);
      rollerOUT();
      wait(500);
      bar(0);
      setMotor(ROLL_LR1, 0);
      arm(0);
      arm(127);
      wait(200);
      arm(0);
      runCone = 1;
    }   
  }
  taskDelete(basePID_1);
  driveSpeed(0);
  mogo(0);
}

inline void //direction; blue is 1 and right is -1
mogoAutonSlave(int direction) {
  gyroReset(GYRO_LR1);
  int gyroPos = direction * 135;
  TaskHandle basePID_2 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  if(direction == 1) {
    while (gyroGet(GYRO_LR1) < gyroPos) {
      delay(15);
    }
  }
  else {
    while (gyroGet(GYRO_LR1) > gyroPos) {
      delay(15);
    }
  }
  taskDelete(basePID_2);
  driveSpeed(0);
  encoderReset(ENC_RIGHT);
  int drivePos = 550;
  TaskHandle basePID_3 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void * ) drivePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  taskDelete(basePID_3);
  driveSpeed(0);
  gyroPos = direction  * 225;
  TaskHandle basePID_4 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  if(direction == 1) {
    while (gyroGet(GYRO_LR1) < gyroPos) {
      delay(15);
    }
  }
  else {
    while (gyroGet(GYRO_LR1) > gyroPos) {
      delay(15);
    }
  }
  taskDelete(basePID_4);
  driveSpeed(0);
  TaskHandle moveBase_5 = taskRunLoop(driveForward, 50);
  delay(1000);
  mogo(127);
  delay(900);
  taskDelete(moveBase_5);
  driveSpeed(0);
  mogo(0);
  TaskHandle moveBase_6 = taskRunLoop(driveBackward, 50);
  delay(500);
  taskDelete(moveBase_6);
  driveSpeed(0);
  mogo(-127);
  wait(600);
  mogo(0);
}

void
autonomous() {
  if(analogRead(AUTO_SENSOR) > 4000) { //blue
    mogoAutonMaster();
    mogoAutonSlave(1);
  }
  else if(analogRead(AUTO_SENSOR) < 100) { //red
   mogoAutonMaster();
   mogoAutonSlave(-1);
  }
}
