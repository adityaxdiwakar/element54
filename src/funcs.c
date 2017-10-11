#include <main.h>

inline void driveCustomVert(int custom) {
  motorSet(CHASSIS_L1, custom);
  motorSet(CHASSIS_L2, -custom);
  motorSet(CHASSIS_R2, custom);
  motorSet(CHASSIS_R1, -custom);
}

inline void driveCustomHort(int custom) {
  setMotor(CHASSIS_L1, custom);
  setMotor(CHASSIS_L2, -custom);
  setMotor(CHASSIS_R2, custom);
  setMotor(CHASSIS_R1, -custom);
}

inline void driveForward() {
  setMotor(CHASSIS_L1, -127);
  setMotor(CHASSIS_L2, 127);
  setMotor(CHASSIS_R2, 127);
  setMotor(CHASSIS_R1, -127);
}

inline void driveBackward() {
  setMotor(CHASSIS_L1, 127);
  setMotor(CHASSIS_L2, -127);
  setMotor(CHASSIS_R2, -127);
  setMotor(CHASSIS_R1, 127);
}

inline void driveLeft() {
  setMotor(CHASSIS_L1, 127);
  setMotor(CHASSIS_L2, -127);
  setMotor(CHASSIS_R2, 127);
  setMotor(CHASSIS_R1, -127);
}

inline void driveRight() {
  setMotor(CHASSIS_L1, -127);
  setMotor(CHASSIS_L2, 127);
  setMotor(CHASSIS_R2, -127);
  setMotor(CHASSIS_R1, 127);
}

inline void driveStop() {
  setMotor(CHASSIS_L1, 0);
  setMotor(CHASSIS_L2, 0);
  setMotor(CHASSIS_R2, 0);
  setMotor(CHASSIS_R1, 0);
}

void driveLeftPivot() {
  setMotor(CHASSIS_L1, 127);
  setMotor(CHASSIS_L2, -127);
}

/*
void posSetArm(void *armPos) {
  if (analogRead(ARM_SENSOR) > *(int *)armPos) {
    while (analogRead(ARM_SENSOR) > *(int *)armPos) {
      arm(-127); }
    arm(0);
    taskDelete(NULL);
  }
  if (analogRead(ARM_SENSOR) < *(int *)armPos) {
    while (analogRead(ARM_SENSOR) < *(int *)armPos) {
      arm(127); }
    arm(0);
    taskDelete(NULL);
  }
}*/

/*void posSetTurn(void *turnRad) {
  int radTurn = (int)turnRad;
  while (true) {
  int iOutput = iRotatePID(radTurn);
  if (gyroGet(GYRO_LR1) > radTurn + 1) {
    driveCustomHort(iOutput);
  } else if (gyroGet(GYRO_LR1) < radTurn - 1) {
    driveCustomHort(iOutput);
  } else
    break;
  delay(15);
}
  chain(0);
  taskDelete(NULL);
}*/

void posSetChain(void *chainPos) {
  int posChain = (int)chainPos;
  while (true) {
    if (analogRead(CHAIN_SENSOR) > posChain + 50) {
      chain(-127);
    } else if (analogRead(CHAIN_SENSOR) < posChain - 50) {
      chain(127);
    } else
      break;
    delay(15);
  }
  chain(0);
  taskDelete(NULL);
}

void posSetMogo(void *mogoPos) {
  int posMogo = (int)mogoPos;
  while (true) {
    if (analogRead(MOGO_SENSOR) > posMogo + 50) {
      mobileGoal(-127);
    } else if (analogRead(MOGO_SENSOR) < posMogo - 50) {
      mobileGoal(127);
    } else
      break;
    delay(15);
  }
  mobileGoal(0);
  taskDelete(NULL);
}

void posSetArm(void *armPos) {
  int posArm = (int)armPos;
  while (true) {
    if (analogRead(ARM_SENSOR) > posArm + 50) {
      arm(-127);
    } else if (analogRead(ARM_SENSOR) < posArm - 50) {
      arm(127);
    } else
      break;
    delay(15);
  }
  arm(0);
  taskDelete(NULL);
}

void posSetBase(void *basePos) {
  if (encoderGet(ENC_LEFT) > (int)basePos) {
    while (encoderGet(ENC_LEFT) > (int)basePos) {
      driveBackward();
    }
    driveStop();
    taskDelete(NULL);
  }
  if (encoderGet(ENC_LEFT) < (int)basePos) {
    while (encoderGet(ENC_LEFT) < (int)basePos) {
      driveForward();
    }
    driveStop();
    taskDelete(NULL);
  }
}

void posPIDBaseFWD(void *basePID_pos) {
  while (true) {
    int driveOutput = iDrivePID((int)basePID_pos);
    driveCustomVert(driveOutput);
    delay(20);
    if (encoderGet(ENC_LEFT) >= (int)basePID_pos) break; }
  driveStop();
  taskDelete(NULL);
}

void posPIDBaseBWD(void *basePID_pos) {
  while(true) {
    int driveOutput = iDrivePID((int) basePID_pos);
    driveCustomVert(driveOutput);
    delay(20);
    if(encoderGet(ENC_LEFT) <= (int)basePID_pos) break;
  }
}

void openPincher() {
  pincher(-127);
}

void beginning_coneAuton(int armPos, int basePos) {
  TaskHandle armMove = taskCreate(posSetArm, TASK_DEFAULT_STACK_SIZE,
                                  (void *)armPos, TASK_PRIORITY_DEFAULT);
  while (analogRead(ARM_SENSOR) < 1200)
    delay(15);
  TaskHandle baseMove = taskCreate(posSetBase, TASK_DEFAULT_STACK_SIZE,
                                   (void *)basePos, TASK_PRIORITY_DEFAULT);
  while (analogRead(ARM_SENSOR) < 1360 && encoderGet(ENC_LEFT) < 190) {
    delay(15);
  }
}

void mogoHoldDown() {
  mobileGoal(127);
}
