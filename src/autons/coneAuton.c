#include  "main.h"


void coneAutonLeft() {
  //startAuton();
  //starts in a position already opened
  beginning_coneAuton(1360, 190); delay(300);
  TaskHandle pinchOpen = taskCreate(openPincher, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  wait(1000); pincher(0); taskDelete(pinchOpen);
}

void mogoAutonRed() {
  startSequence();
  int basePos = 900;
  int armPos = 1200;
  int mogoPos = 2800;
  TaskHandle armMove = taskCreate(posSetArm, TASK_DEFAULT_STACK_SIZE, (void*)armPos, TASK_PRIORITY_DEFAULT);
  while(analogRead(ARM_SENSOR) < armPos) delay(15);
  TaskHandle holdMogo = taskRunLoop(mogoHoldDown, 1); wait(500);
  TaskHandle baseMove = taskCreate(posSetBase, TASK_DEFAULT_STACK_SIZE, (void*)basePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_LEFT) < basePos && analogRead(MOGO_SENSOR) < mogoPos) delay(15);
  wait(300); taskDelete(holdMogo); wait(500);
  mogoPos = 15;
  TaskHandle mogoMove2 = taskCreate(posSetMogo, TASK_DEFAULT_STACK_SIZE, (void*)mogoPos, TASK_PRIORITY_DEFAULT);
  while(analogRead(MOGO_SENSOR) > mogoPos) delay(15);
  driveBackward();
  while(encoderGet(ENC_LEFT) > 500) delay(15);
  driveStop();
  wait(250);
  while(encoderGet(ENC_LEFT) > basePos) delay(15);
  int turnRad = 42;
  TaskHandle firstTurn = taskCreate(posSetTurn, TASK_DEFAULT_STACK_SIZE, (void*)turnRad, TASK_PRIORITY_DEFAULT);
  wait(600);
  taskDelete(firstTurn);
  driveStop(); chain(0);
  encoderReset(ENC_LEFT);
  int back = -420;
  TaskHandle driveMid = taskCreate(posSetBase, TASK_DEFAULT_STACK_SIZE, (void*)back, TASK_PRIORITY_DEFAULT);
  while(encoderGet(ENC_LEFT) > -380) delay(15);
  driveStop();
  turnRad = 133;
  TaskHandle secondTurn = taskCreate(posSetTurn, TASK_DEFAULT_STACK_SIZE, (void*)turnRad, TASK_PRIORITY_DEFAULT);
  wait(900);
  taskDelete(secondTurn);
  driveStop();
  arm(-127);
  while(analogRead(ARM_SENSOR) > 1000) delay(15);
  arm(0);
  TaskHandle movePincher = taskRunLoop(openPincher, 1); wait(200);
  armPos = 1150;
  TaskHandle surgeArm = taskCreate(posSetArm, TASK_DEFAULT_STACK_SIZE, (void*)armPos, TASK_PRIORITY_DEFAULT);
  while(analogRead(ARM_SENSOR) < 1150) delay(15);
  arm(0);
  taskDelete(movePincher); pincher(0);
  TaskHandle equalizeBase = taskRunLoop(driveForward, 1); wait(1500); taskDelete(equalizeBase);
  TaskHandle holdBase = taskRunLoop(slowDriveForward,1); wait(500);
  TaskHandle drop20 = taskRunLoop(mogoHoldDown, 1); wait(1700);
  mobileGoal(0); taskDelete(drop20); driveStop(); wait(300); taskDelete(holdBase); TaskHandle escape = taskRunLoop(driveBackward, 1); wait(1000); driveStop();
  taskDelete(escape);
}

  void mogoAutonBlue() {
    startSequence();
    int basePos = 900;
    int armPos = 1200;
    int mogoPos = 2800;
    TaskHandle armMove = taskCreate(posSetArm, TASK_DEFAULT_STACK_SIZE, (void*)armPos, TASK_PRIORITY_DEFAULT);
    while(analogRead(ARM_SENSOR) < armPos) delay(15);
    TaskHandle holdMogo = taskRunLoop(mogoHoldDown, 1); wait(500);
    TaskHandle baseMove = taskCreate(posSetBase, TASK_DEFAULT_STACK_SIZE, (void*)basePos, TASK_PRIORITY_DEFAULT);
    while (encoderGet(ENC_LEFT) < basePos && analogRead(MOGO_SENSOR) < mogoPos) delay(15);
    wait(300); taskDelete(holdMogo); wait(500);
    mogoPos = 15;
    TaskHandle mogoMove2 = taskCreate(posSetMogo, TASK_DEFAULT_STACK_SIZE, (void*)mogoPos, TASK_PRIORITY_DEFAULT);
    while(analogRead(MOGO_SENSOR) > mogoPos) delay(15);
    driveBackward();
    while(encoderGet(ENC_LEFT) > 500) delay(15);
    driveStop();
    wait(250);
    while(encoderGet(ENC_LEFT) > basePos) delay(15);
    int turnRad = -42;
    TaskHandle firstTurn = taskCreate(posSetTurn, TASK_DEFAULT_STACK_SIZE, (void*)turnRad, TASK_PRIORITY_DEFAULT);
    wait(600);
    taskDelete(firstTurn);
    driveStop(); chain(0);
    encoderReset(ENC_LEFT);
    int back = -420;
    TaskHandle driveMid = taskCreate(posSetBase, TASK_DEFAULT_STACK_SIZE, (void*)back, TASK_PRIORITY_DEFAULT);
    while(encoderGet(ENC_LEFT) > -380) delay(15);
    driveStop();
    turnRad = -133;
    TaskHandle secondTurn = taskCreate(posSetTurn, TASK_DEFAULT_STACK_SIZE, (void*)turnRad, TASK_PRIORITY_DEFAULT);
    wait(900);
    taskDelete(secondTurn);
    driveStop();
    arm(-127);
    while(analogRead(ARM_SENSOR) > 1000) delay(15);
    arm(0);
    TaskHandle movePincher = taskRunLoop(openPincher, 1); wait(200);
    armPos = 1150;
    TaskHandle surgeArm = taskCreate(posSetArm, TASK_DEFAULT_STACK_SIZE, (void*)armPos, TASK_PRIORITY_DEFAULT);
    while(analogRead(ARM_SENSOR) < 1150) delay(15);
    arm(0);
    taskDelete(movePincher); pincher(0);
    TaskHandle equalizeBase = taskRunLoop(driveForward, 1); wait(1500); taskDelete(equalizeBase);
    TaskHandle holdBase = taskRunLoop(slowDriveForward,1); wait(500);
    TaskHandle drop20 = taskRunLoop(mogoHoldDown, 1); wait(1700);
    mobileGoal(0); taskDelete(drop20); driveStop(); wait(300); taskDelete(holdBase); TaskHandle escape = taskRunLoop(driveBackward, 1); wait(1000); driveStop();
    taskDelete(escape);
    }

void startSequence() {
  //lift up slight 545->600
  //mogo back 267->6
  arm(127);
  wait(250);
  arm(20);
  wait(100);
  TaskHandle bringMogo = taskRunLoop(getMogo, 1);
  wait(100);
  mobileGoal(0); taskDelete(bringMogo);
}
