/* Header of autonomous file */

#include "main.h"

/* 
 * Picks up mobile goal with options to stack preload cone, and additional cone
 * Does not do any turns, picks up goal and drives back to poal
 * To be paired with the mogoAutonSlave
 */
inline void
mogoAutonMaster(int coneCount) {
  gyroReset(GYRO_LR1);
  encoderReset(ENC_RIGHT);
  int armPos = 2000;
  int mogoPos = 3000;
  int drivePos = 1200;
  int barPos = 350;
  int runCone = 0;
  arm(127);
  TaskHandle barMove_1 = taskCreate(barDown, TASK_DEFAULT_STACK_SIZE, (void * ) barPos, TASK_PRIORITY_DEFAULT);
  TaskHandle armMove_1 = taskCreate(armUp, TASK_DEFAULT_STACK_SIZE, (void * ) armPos, TASK_PRIORITY_DEFAULT);
  while (analogRead(ARM_SENSOR) < armPos - 500) {
    delay(15);
  }
  mogo(127);
  driveSpeed(127);
  while (analogRead(MOGO_SENSOR) < mogoPos || analogRead(ARM_SENSOR) < armPos || encoderGet(ENC_RIGHT) < drivePos - 200) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > mogoPos) mogo(30);
    if (analogRead(ARM_SENSOR) > armPos) arm(0);
    if (encoderGet(ENC_RIGHT) > drivePos - 200) driveSpeed(0);
  }
  driveSpeed(127);
  while (encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  driveSpeed(0);
  wait(250);
  encoderReset(ENC_RIGHT);
  mogoPos = 1300;
  drivePos = -1100;
  bar(127);
  mogo(-127);
  while (analogRead(MOGO_SENSOR) > 1700) {
    delay(15);
    mogo(-127);
  }
  delay(200);
  mogo(0);
  bar(0);
  armPos = 1700;
  arm(-127);
  bar(63);
  setMotor(ROLL_LR1, -63);
  taskDelete(barMove_1);
  taskDelete(armMove_1);
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
  taskDelete(armMove_2);
  if (coneCount == 2) {
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
    wait(150);
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
  }
  TaskHandle basePID_1 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void * ) drivePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_RIGHT) > drivePos || runCone == 0) {
    delay(15);
    if (runCone == 0) {
      int armCurr = analogRead(ARM_SENSOR);
      arm(127);
      while (analogRead(ARM_SENSOR) < armCurr + 125) delay(15);
      arm(0);
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
  delay(500);
}

/* 
 * To be paired with a autonMaster
 * Completes a turn and places mobile goal in 20 point zone
 * 1 = Blue; -1 = Red (for 20pt)
 */
inline void
mogoAutonSlave(int direction) {
  int gyroPos = direction * 135;
  TaskHandle basePID_2 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  if (direction == 1) {
    while (gyroGet(GYRO_LR1) < gyroPos) {
      delay(15);
    }
  } else {
    while (gyroGet(GYRO_LR1) > gyroPos) {
      delay(15);
    }
  }
  wait(150);
  taskDelete(basePID_2);
  driveSpeed(0);
  wait(250);
  int drivePos = 500;
  encoderReset(ENC_RIGHT);
  TaskHandle basePID_3 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void * ) drivePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  wait(150);
  taskDelete(basePID_3);
  driveSpeed(0);
  wait(250);
  gyroPos = direction * 225;
  TaskHandle basePID_4 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  if (direction == 1) {
    while (gyroGet(GYRO_LR1) < gyroPos) {
      delay(15);
    }
  } else {
    while (gyroGet(GYRO_LR1) > gyroPos) {
      delay(15);
    }
  }
  wait(150);
  taskDelete(basePID_4);
  driveSpeed(0);
  wait(250);
  TaskHandle moveBase_5 = taskRunLoop(driveForward, 50);
  delay(750);
  mogo(127);
  delay(750);;
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

/* 
 * To be paired with a autonMaster
 * Completes a turn and places mobile goal in 5 point zone
 * -1 = Blue; 1 = Red (for 5pt)
 */

inline void
mogoAuton5(int direction) {
  int gyroPos = direction * 175;
  TaskHandle basePID_2 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  if (direction == 1) {
    while (gyroGet(GYRO_LR1) < gyroPos) {
      delay(15);
    }
  } else {
    while (gyroGet(GYRO_LR1) > gyroPos) {
      delay(15);
    }
  }
  wait(250);
  taskDelete(basePID_2);
  driveSpeed(0);
  mogo(127);
  wait(1050);
  mogo(0);
  driveBackward();
  wait(1000);
  driveSpeed(0);
}

/*
int holder, gyroPos;
inline void
newprogSkills() {
  holder = analogRead(ARM_SENSOR); arm(127); 
  while(analogRead(ARM_SENSOR) < holder + 15) {
    delay(15);
  }
  driveSpeed(127);
  mogo(127);
  while(analogRead(ARM_SENSOR) < holder + 50 || analogRead(MOGO_SENSOR) < 3000 || encoderGet(ENC_RIGHT) < 1000) {
    delay(15);
    if(analogRead(ARM_SENSOR) > holder + 50) { arm(0); }
    if(analogRead(MOGO_SENSOR) > 3000) { mogo(30); }
    if(encoderGet(ENC_RIGHT) > 1000) { driveSpeed(30); }
  }
  driveSpeed(127);
  while(encoderGet(ENC_RIGHT) < 1250) { delay(15); }
  driveSpeed(0);
  mogo(-127);
  while(analogRead(MOGO_SENSOR) > 1750) { delay(15); }
  wait(1000); mogo(-30);
  driveSpeed(-127); holder = 0;
  while(encoderGet(ENC_RIGHT) > 100 || !holder) {
    delay(15);
    if(holder == 0) {
      arm(-127); wait(50); arm(127); wait(100);
      bar(127); wait(500); arm(-127); wait(25);
      rollerOUT(); arm(127); wait(150); arm(0);
      holder = 1;
    }
    if(encoderGet(ENC_RIGHT) < 100) { driveSpeed(0); }
  }
  gyroPos = -135;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500); taskDelete(rotate);
  driveSpeed(0); encoderReset(ENC_RIGHT);
  driveSpeed(127); 
  while(encoderGet(ENC_RIGHT) < 500) { delay(15); }
  gyroPos = -225;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500); taskDelete(rotate);
  TaskHandle moveBase_5 = taskRunLoop(driveForward, 50);
  delay(750); mogo(127); delay(750);;
  taskDelete(moveBase_5); driveSpeed(0);
  mogo(0); TaskHandle moveBase_6 = taskRunLoop(driveBackward, 50);
  delay(500); taskDelete(moveBase_6); driveSpeed(0);
  mogo(-127); wait(600); mogo(0);
  driveBackward(); wait(850); driveSpeed(50); 
  wait(750); gyroReset(GYRO_LR1); driveSpeed(-63);
  wait(250); driveSpeed(0); gyroPos = -90;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500); taskDelete(rotate); driveSpeed(0);
  mogo(127); driveSpeed(127); encoderReset(ENC_RIGHT);
  while(encoderGet(ENC_RIGHT) < 450) { delay(15); }
}
*/

inline void
boonkTheMogo() {
  TaskHandle rotate;
  driveForward();
  while (encoderGet(ENC_RIGHT) < 500) {
    delay(15);
  }
  driveSpeed(0);
  int gyroPos = 45;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500);
  taskDelete(rotate);
  driveSpeed(0);
  encoderReset(ENC_RIGHT);
  driveForward();
  while (encoderGet(ENC_RIGHT) < 1000) {
    delay(15);
  }
  driveSpeed(0);
  gyroPos = -45;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500);
  taskDelete(rotate);
  driveSpeed(0);
  encoderReset(ENC_RIGHT);
  driveForward();
  while (encoderGet(ENC_RIGHT) < 500) {
    delay(15);
  }
  driveSpeed(0);
  gyroPos = -90;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500);
  taskDelete(rotate);
  driveSpeed(0);
  driveForward();
  wait(250);
  driveSpeed(0);
  mogo(-127);
  while (analogRead(MOGO_SENSOR) > 1750) {
    delay(15);
  }
  mogo(-20);
  driveBackward();
  wait(250);
  driveSpeed(0);
  gyroPos = -45;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500);
  taskDelete(rotate);
  driveSpeed(0);
  encoderReset(ENC_RIGHT);
  driveBackward();
  while (encoderGet(ENC_RIGHT) > -500) {
    delay(15);
  }
  driveSpeed(0);
  gyroPos = -135;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500);
  taskDelete(rotate);
  encoderReset(ENC_RIGHT);
  driveSpeed(0);
  driveForward();
  while (encoderGet(ENC_RIGHT) < 1000) {
    delay(15);
  }
  gyroPos = -180;
  rotate = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500);
  taskDelete(rotate);
  driveSpeed(0);
  driveForward();
  wait(250);
  mogo(127);
  wait(500);
  mogo(0);
  driveBackward();
  wait(300);
  driveSpeed(0);
}

/* 
 * Align specifically with equal spacing on left and right
 * Hard objective code for RED side to start with 20 point
 * Currently 72 points (2 in 20, 3 in 10, and 1 cone)
 */
inline void
progSkills() {
  //start first mogo
  mogoAutonMaster(2);
  mogoAutonSlave(-1);
  //end first mogo

  //start second mogo
  driveBackward();
  wait(850);
  driveSpeed(50);
  wait(750);
  gyroReset(GYRO_LR1);
  driveSpeed(-63);
  wait(250);
  driveSpeed(0);
  int gyroPos = -93;
  int armCount = 0;
  TaskHandle basePID_2 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
    if (!armCount) {
      arm(127);
      wait(50);
      arm(0);
      armCount = 1;
    }
  }
  wait(500);
  taskDelete(basePID_2);
  driveSpeed(0);
  wait(300);
  encoderReset(ENC_RIGHT);
  int drivePos = 400;
  driveForward();
  TaskHandle moveBase_3 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void * ) drivePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  wait(500);
  driveSpeed(0);
  taskDelete(moveBase_3);
  wait(300);
  gyroPos = -200;
  mogo(127);
  TaskHandle basePID_3 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > 3000) {
      mogo(63);
    }
  }
  wait(500);
  driveSpeed(0);
  taskDelete(basePID_3);
  driveSpeed(-30);
  wait(1000);
  gyroReset(GYRO_LR1);
  while (analogRead(MOGO_SENSOR) < 3000) {
    mogo(127);
  }
  mogo(63);
  encoderReset(ENC_RIGHT);
  driveForward();
  while (encoderGet(ENC_RIGHT) < 1250) {
    delay(15);
  }
  driveSpeed(0);
  mogo(-127);
  while (analogRead(MOGO_SENSOR) > 1770) {
    delay(15);
  }
  wait(250);
  mogo(0);
  gyroPos = -183;
  TaskHandle basePID_4 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(250);
  driveSpeed(0);
  taskDelete(basePID_4);
  encoderReset(ENC_RIGHT);
  driveForward();
  mogo(127);
  while (encoderGet(ENC_RIGHT) < 825) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > 2300) {
      mogo(-10);
    }
  }
  driveSpeed(127);
  wait(675);
  gyroReset(GYRO_LR1);
  driveSpeed(0);
  driveBackward();
  wait(100);
  //end second mogo

  //start third mogo
  driveSpeed(-127);
  wait(100);
  driveSpeed(0);
  gyroPos = 90;
  TaskHandle basePID_6 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) < gyroPos) {
    delay(15);
  }
  wait(500);
  driveSpeed(0);
  taskDelete(basePID_6);
  driveSpeed(127);
  encoderReset(ENC_RIGHT);
  drivePos = 775;
  driveForward();
  TaskHandle moveBase_4 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void * ) drivePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  wait(500);
  driveSpeed(0);
  taskDelete(moveBase_4);
  wait(300);

  gyroPos = 180;
  mogo(127);
  TaskHandle basePID_7 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) < gyroPos) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > 3000) {
      mogo(63);
    }
  }
  wait(250);
  driveSpeed(0);
  taskDelete(basePID_7);
  while (analogRead(MOGO_SENSOR) < 3000) {
    mogo(127);
  }
  mogo(63);
  encoderReset(ENC_RIGHT);
  driveForward();
  wait(1250);
  driveSpeed(0);
  mogo(-127);
  while (analogRead(MOGO_SENSOR) > 1770) {
    delay(15);
  }
  wait(250);
  mogo(0);
  gyroPos = 0;
  TaskHandle basePID_20 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(250);
  driveSpeed(0);
  taskDelete(basePID_20);
  encoderReset(ENC_RIGHT);
  driveForward();
  mogo(127);
  while (encoderGet(ENC_RIGHT) < 825) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > 2300) {
      mogo(-10);
    }
  }
  driveSpeed(127);
  wait(575);
  driveSpeed(0);
  driveBackward();
  wait(500);

  //start third mogo
  gyroPos = 180;
  TaskHandle basePID_5 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500);
  driveSpeed(0);
  taskDelete(basePID_5);
  wait(250);
  encoderReset(ENC_RIGHT);
  driveForward();
  mogo(127);
  bar(-63);
  while (encoderGet(ENC_RIGHT) < 1500) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > 3000) {
      mogo(40);
    }
  }
  mogo(-127);
  while (encoderGet(ENC_RIGHT) < 2250) {
    delay(15);
    if (analogRead(MOGO_SENSOR) < 2700) {
      mogo(-10);
    }
  }
  bar(-20);
  driveSpeed(127);
  wait(500);
  driveSpeed(63);
  wait(50);
  gyroReset(GYRO_LR1);
  //end third mogo

  //start fourth mogo
  driveSpeed(-127);
  wait(150);
  driveSpeed(0);
  gyroPos = 90;
  TaskHandle basePID_26 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(500);
  driveSpeed(0);
  taskDelete(basePID_26);
  driveSpeed(127);
  encoderReset(ENC_RIGHT);
  drivePos = 775;
  driveForward();
  TaskHandle moveBase_29 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void * ) drivePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  wait(500);
  driveSpeed(0);
  taskDelete(moveBase_29);
  wait(300);

  gyroPos = 180;
  mogo(127);
  TaskHandle basePID_27 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > 3000) {
      mogo(63);
    }
  }
  wait(250);
  driveSpeed(0);
  taskDelete(basePID_27);
  while (analogRead(MOGO_SENSOR) < 3000) {
    mogo(127);
  }
  mogo(63);
  encoderReset(ENC_RIGHT);
  driveForward();
  wait(1250);
  driveSpeed(0);
  mogo(-127);
  while (analogRead(MOGO_SENSOR) > 1770) {
    delay(15);
  }
  wait(250);
  mogo(0);
  gyroPos = 0;
  TaskHandle basePID_8 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) < gyroPos) {
    delay(15);
  }
  wait(250);
  driveSpeed(0);
  taskDelete(basePID_8);
  encoderReset(ENC_RIGHT);
  driveForward();
  mogo(127);
  while (encoderGet(ENC_RIGHT) < 750) {
    delay(15);
    if (analogRead(MOGO_SENSOR) < 1800) {
      mogo(0);
    }
  }
  mogo(0);
  gyroPos = -45;
  TaskHandle basePID_9 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(250);
  driveSpeed(0);
  taskDelete(basePID_9);
  wait(250);
  encoderReset(ENC_RIGHT);
  driveForward();
  while (encoderGet(ENC_RIGHT) < 500) {
    delay(15);
  }
  gyroPos = 0;
  TaskHandle basePID_10 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(250);
  taskDelete(basePID_10);
  driveSpeed(0);
  TaskHandle moveBase_10 = taskRunLoop(driveForward, 50);
  delay(750);
  mogo(127);
  delay(750);
  taskDelete(moveBase_10);
  driveSpeed(0);
  mogo(0);
  TaskHandle moveBase_11 = taskRunLoop(driveBackward, 50);
  delay(500);
  taskDelete(moveBase_11);
  driveSpeed(0);
  mogo(-127);
  wait(600);
  mogo(0);
  //end fourth mogo

  //start fifth mogo
  driveBackward();
  wait(850);
  driveSpeed(50);
  wait(750);
  driveSpeed(-63);
  wait(250);
  driveSpeed(0);
  gyroPos = -90;
  TaskHandle basePID_12 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
  }
  wait(250);
  taskDelete(basePID_12);
  driveSpeed(0);
  encoderReset(ENC_RIGHT);
  drivePos = 325;
  driveForward();
  TaskHandle moveBase_12 = taskCreate(driveToPID, TASK_DEFAULT_STACK_SIZE, (void * ) drivePos, TASK_PRIORITY_DEFAULT);
  while (encoderGet(ENC_RIGHT) < drivePos) {
    delay(15);
  }
  wait(500);
  driveSpeed(0);
  taskDelete(moveBase_12);
  wait(300);

  gyroPos = -180;
  mogo(127);
  TaskHandle basePID_11 = taskCreate(rotateToPID, TASK_DEFAULT_STACK_SIZE, (void * ) gyroPos, TASK_PRIORITY_DEFAULT);
  while (gyroGet(GYRO_LR1) > gyroPos) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > 3000) {
      mogo(63);
    }
  }
  wait(500);
  driveSpeed(0);
  taskDelete(basePID_11);
  while (analogRead(MOGO_SENSOR) < 3000) {
    mogo(127);
  }
  mogo(63);
  wait(250);
  encoderReset(ENC_RIGHT);
  driveForward();
  mogo(-127);
  while (encoderGet(ENC_RIGHT) < 2000) {
    delay(15);
    if (analogRead(MOGO_SENSOR) > 2700) {
      mogo(-10);;
    }
  }
  while (encoderGet(ENC_RIGHT) < 2250) {
    delay(15);
  }
  driveSpeed(127);
  wait(850);
  gyroReset(GYRO_LR1);
  driveSpeed(-127);
  wait(500);
  driveSpeed(0);
  //end fifth mogo */
}

/* 
 * Globally defined function for autonomous
 * Simple potentiometer selector; Neutron messages sent for 
 * selected auton and allows for added and removed using
 * smaller margins of errors for selection ranges
 */
void
autonomous() {
  if (analogRead(AUTO_SENSOR) > 4000) { //blue
    mogoAutonMaster(2);
    mogoAutonSlave(1);
  } else if (analogRead(AUTO_SENSOR) < 100) { //red
    mogoAutonMaster(2);
    mogoAutonSlave(-1);
  } else {
    //do nothing
  }
}

/* Footer of autonomous file */