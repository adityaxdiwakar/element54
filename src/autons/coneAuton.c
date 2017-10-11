#include  "main.h"


inline void startAuton() {
}

void coneAutonLeft() {
  //startAuton();
  //starts in a position already opened
  beginning_coneAuton(1360, 190); delay(300);
  TaskHandle driveBack = taskRunLoop(driveBackward, 50);
  wait(500); driveStop(); taskDelete(driveBack);
  TaskHandle pinchOpen = taskCreate(openPincher, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  wait(1000); pincher(0); taskDelete(pinchOpen);
}

void coneAutonHyp() {
  //startAuton();
  //starts in an open position
  beginning_coneAuton(1360, 1060);
  TaskHandle driveBack = taskRunLoop(driveBackward,50);
  wait(500); driveStop(); taskDelete(driveBack);
  TaskHandle pinchOpen = taskCreate(openPincher, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  wait(500); pincher(0); taskDelete(pinchOpen);
}

void mogoAuton() {
  //startAuton();
  //starts in an open position
  //350

  int basePos = 1000;
  int armPos = 1100;
  int mogoPos = 2800;
  int chainPos = 1700;
  TaskHandle armMove = taskCreate(posSetArm, TASK_DEFAULT_STACK_SIZE, (void*)armPos, TASK_PRIORITY_DEFAULT);
  while(analogRead(ARM_SENSOR) < armPos) delay(15);
  TaskHandle holdMogo = taskRunLoop(mogoHoldDown, 1); wait(500);
  TaskHandle baseMove = taskCreate(posSetBase, TASK_DEFAULT_STACK_SIZE, (void*)basePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_LEFT) < basePos && analogRead(MOGO_SENSOR) < mogoPos) delay(15);
  wait(1000); taskDelete(holdMogo); wait(250);
  mogoPos = 15;
  TaskHandle mogoMove2 = taskCreate(posSetMogo, TASK_DEFAULT_STACK_SIZE, (void*)mogoPos, TASK_PRIORITY_DEFAULT);
  while(analogRead(MOGO_SENSOR) > mogoPos) delay(15);
  basePos = 300;
  TaskHandle chainMove = taskCreate(posSetChain, TASK_DEFAULT_STACK_SIZE, (void*)chainPos, TASK_PRIORITY_DEFAULT);
  TaskHandle armMove2 = taskCreate(posPIDBaseBWD, TASK_DEFAULT_STACK_SIZE, (void*)basePos, TASK_PRIORITY_DEFAULT);
  while(analogRead(CHAIN_SENSOR) < chainPos && encoderGet(ENC_LEFT) > basePos) delay(15);
  chain(0); TaskHandle pivotBase = taskRunLoop(driveLeftPivot, 1); wait(350);
  TaskHandle movePincher = taskRunLoop(openPincher, 1);
  while(gyroGet(GYRO_LR1) < 137) delay(15);
  pincher(0); taskDelete(movePincher); driveStop(); taskDelete(pivotBase);
  TaskHandle equalizeBase = taskRunLoop(driveForward, 1); wait(1000);
  driveStop(); taskDelete(equalizeBase); wait(500); TaskHandle revBase_1 = taskRunLoop(driveBackward, 1); wait(500);
  driveStop(); taskDelete(revBase_1); wait(250); TaskHandle revBase_2 = taskRunLoop(driveForward, 1); wait(1000);
  taskDelete(revBase_2); TaskHandle drop20 = taskRunLoop(mogoHoldDown, 1); wait(1000);
  TaskHandle escape = taskRunLoop(driveBackward, 1); wait(1000); mobileGoal(0); taskDelete(drop20); driveStop();
  taskDelete(escape);

  }
