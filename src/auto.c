#include "main.h"

inline void
coneEscape() {
  setMotor(ROLL_LR1, -127);
  driveSpeed(127);
  wait(400); //500
  bar(127);
  wait(100);
  driveSpeed(-127);
  wait(300); //400
  driveSpeed(0);
  bar(127);
  while(analogRead(BAR_SENSOR) > 400) {
    delay(15);
  }
  arm(0);
  bar(0);
  wait(500);
  arm(127);
  while(analogRead(ARM_SENSOR) < 2400) {
    delay(15);
  }
  arm(0);
  mogo(127);
  wait(500);
  driveSpeed(127);
  wait(500);
  mogo(0);
  driveSpeed(0);
  wait(500);
  rollerOUT();
  wait(1000);
  driveSpeed(-127);
  wait(250);
  driveSpeed(0);
  wait(250);
  driveTurn(-127);
  wait(400);
  driveTurn(0);
  wait(250);
  driveSpeed(127);
  wait(750);
  driveSpeed(0);
}

inline void
uni_mogoDefaultBeginDefault() {
  encoderReset(ENC_RIGHT);

  int armPos = 2000;
  int mogoPos = 3000;
  int drivePos = 1250;
  int barPos = 350;
  setMotor(ROLL_LR1, -63);
  arm(127);
  bar(127);
  TaskHandle barMove_1 = taskCreate(barDown, TASK_DEFAULT_STACK_SIZE, (void*)barPos, TASK_PRIORITY_DEFAULT);
  TaskHandle armMove_1 = taskCreate(armUp, TASK_DEFAULT_STACK_SIZE, (void*)armPos, TASK_PRIORITY_DEFAULT);
  while(analogRead(ARM_SENSOR) < armPos) {
    delay(15);
  }
  arm(0);
  mogo(127);
  while(analogRead(MOGO_SENSOR) < mogoPos) {
    delay(15);
  }
  mogo(63);
  driveSpeed(127);
  while(encoderGet(ENC_RIGHT) < 1250) {
    delay(15);
  }
  driveSpeed(0);
  delay(500);
  encoderReset(ENC_RIGHT);
  mogoPos = 1500;
  drivePos = -1400;
  mogo(-127);
  while(analogRead(MOGO_SENSOR) > 1700) {
    delay(15);
  }
  mogo(0);
  TaskHandle basePID_1 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void*)drivePos, TASK_PRIORITY_DEFAULT);
  while(encoderGet(ENC_RIGHT) > drivePos) {
    delay(15);
  }
  wait(150);
  taskDelete(basePID_1); driveSpeed(0);
  mogo(0);
  wait(500);
}

inline void
blue_mogoDefaultAfterTurn() {
  gyroReset(GYRO_LR1);
  int gyroPos = 135 ;
  TaskHandle basePID_2 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void*)gyroPos, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO_LR1) < gyroPos) {
    delay(15);
  }
  delay(1000);
  taskDelete(basePID_2); driveSpeed(0); encoderReset(ENC_RIGHT);
  int drivePos = 650;
  TaskHandle basePID_3 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void*)drivePos, TASK_PRIORITY_DEFAULT);
  while(encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  delay(250);
  taskDelete(basePID_3); driveSpeed(0);
  gyroPos = 225;
  TaskHandle basePID_4 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void*)gyroPos, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO_LR1) < gyroPos) {
    delay(15);
  }
  delay(750);
  taskDelete(basePID_4); driveSpeed(0);
  TaskHandle moveBase_5 = taskRunLoop(driveForward, 50);
  delay(250);
  mogo(127);
  delay(1000);
  taskDelete(moveBase_5); driveSpeed(0);
  mogo(0);
  TaskHandle moveBase_6 = taskRunLoop(driveBackward, 50);
  delay(500);
  taskDelete(moveBase_6); driveSpeed(0);
  mogo(-127);
  wait(600);
  mogo(0);
}

inline void
red_mogoDefaultAfterTurn() {
  gyroReset(GYRO_LR1);
  int gyroPos = -135 ;
  TaskHandle basePID_2 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void*)gyroPos, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  delay(1000);
  taskDelete(basePID_2); driveSpeed(0); encoderReset(ENC_RIGHT);
  int drivePos = 650;
  TaskHandle basePID_3 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void*)drivePos, TASK_PRIORITY_DEFAULT);
  while(encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  delay(250);
  taskDelete(basePID_3); driveSpeed(0);
  gyroPos = -225;
  TaskHandle basePID_4 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void*)gyroPos, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  delay(750);
  taskDelete(basePID_4); driveSpeed(0);
  TaskHandle moveBase_5 = taskRunLoop(driveForward, 50);
  delay(250);
  mogo(127);
  delay(1000);
  taskDelete(moveBase_5); driveSpeed(0);
  mogo(0);
  TaskHandle moveBase_6 = taskRunLoop(driveBackward, 50);
  delay(500);
  taskDelete(moveBase_6); driveSpeed(0);
  mogo(-127);
  wait(600);
  mogo(0);
}

inline void
mogoBlue() {
  uni_mogoDefaultBeginDefault();
  blue_mogoDefaultAfterTurn();
}

inline void
mogoRed() {
  uni_mogoDefaultBeginDefault();
  red_mogoDefaultAfterTurn();
}

void
autonomous() {
  if(analogRead(AUTO_SENSOR) > 4000) {
    mogoBlue();
  }
  else if(analogRead(AUTO_SENSOR) < 100) {
    mogoRed();
  }
  else if(analogRead(AUTO_SENSOR) > 2000 && analogRead(AUTO_SENSOR) < 3000) {
    coneEscape();
  }
  else {
    //nothing
  }
}
