#include "auton.h"
#include <Base.h>
#include <Claw.h>
#include <Dumper.h>
#include <MotorDef.h>
#include <arm.h>
#include <claw1.h>
#include <drive.h>

// Drive Custom
void DriveForwardSpeed(int leftsp, int rightsp, int askTime, int time) {
  driveSet(-leftsp, rightsp);
  if (askTime == 1) {
    wait(time);
    driveSet(0, 0);
  }
}

void DriveBackwardSpeed(int leftsp, int rightsp, int askTime, int time) {
  driveSet(leftsp, -rightsp);
  if (askTime == 1) {
    wait(time);
    driveSet(0, 0);
  }
}

void DriveRotateLeftSpeed(int leftsp, int rightsp, int askTime, int time) {
  driveSet(leftsp, rightsp);
  if (askTime == 1) {
    wait(time);
    driveSet(0, 0);
  }
}

void DriveRotateRightSpeed(int leftsp, int rightsp, int askTime, int time) {
  driveSet(-leftsp, -rightsp);
  if (askTime == 1) {
    wait(time);
    driveSet(0, 0);
  }
}

// Arm Custom
void ArmCustomSpeed(int speed, int AskDown, int AskUp, int askTime, int time) {
  if (AskUp == 1) {
    armSet(speed);
    if (AskDown == 1) {
      armSet(-speed);
      if (askTime == 1) {
        wait(time);
        armSet(0);
      }
    }
  }
}

// Flatbed Custom
void FlatbedCustomSpeed(int speed, int AskPULL, int AskPUSH, int askTime,
                        int time) {
  if (AskPULL == 1) {
    motorSet(1, -speed);
    motorSet(10, speed);
  }
  if (AskPUSH == 1) {
    motorSet(1, speed);
    motorSet(10, -speed);
  }
}

void WaitUntilArmPot(int target) {
  while (analogRead(ArmPot) < target) {
    // Loop for no reason
  }
  armSet(0);
}

void WaitUntilArmStable() {
  while (analogReadCalibrated(ArmPot) < 1400) {
    // Loop for no reason
  }
  armSet(0);
}

void WaitUntilArmVert() {
  while (analogReadCalibrated(ArmPot) < 2213) {
    // loop for no reason
  }
  armSet(0);
}

void WaitUntilArmDown() {
  while (digitalRead(DownBumpP) == 1) {
    // loop for no reason
  }
  armSet(0);
}

void WaitUntilBackBump() {
  while (digitalRead(BackBump) == 1) {
    // loop for no reason
  }
  driveSet(0, 0);
}

void FuncRotateGyro(int speed,
                    int GyroRequest) { // based on starting point; not added on
  int Target = GyroRequest;
  int pos = gyroGet(gyro1);
  if (pos > Target) { // required to decrease (turn left)
    while (pos > Target + 150 && pos < Target - 150) {
      DriveRotateLeftSpeed(speed, speed, 0, 0);
    }
    pos = gyroGet(gyro1);
    while (pos > Target + 10 && pos < Target - 10) {
      DriveRotateLeftSpeed(2 * speed / 3, 2 * speed / 3, 0, 0);
      pos = gyroGet(gyro1);
    }
    driveSet(0, 0);
  }
  if (gyroGet(gyro1) < Target) {
    while (pos > Target + 150 && pos < Target - 150) {
      DriveRotateRightSpeed(speed, speed, 0, 0);
      pos = gyroGet(gyro1);
    }
    while (pos > Target + 10 && pos > Target - 10) {
      DriveRotateRightSpeed(2 * speed / 3, 2 * speed / 3, 0, 0);
      pos = gyroGet(gyro1);
    }
    driveSet(0, 0);
  }
}

void AutoCubeLeft() {
  clawSet(-127);
  while (analogRead(ClawPot) < 1200) {
  } // do nothing
  DriveForwardSpeed(127, 127, 0, 0);
  while (analogRead(LeftLIN) > 600) {
  } // Do nothing here
  clawSet(0);
  DriveBackwardSpeed(127, 127, 1, 50);
  DriveRotateRightSpeed(75, 75, 0, 0);
  while (gyroGet(gyro1) < 68) {
    DriveRotateRightSpeed(75, 75, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateLeftSpeed(127, 127, 1, 50);
  while (analogRead(ClawPot) < 2650)
    clawSet(-127); // make it greater //closing claw
  clawSet(0);
  while (analogRead(ClawPot) > 2750)
    clawSet(127); // make it less //opening claw
  clawSet(0);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 450 && encoderGet(enc2) < 450) {
  } // do nothing
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3000) {
  } // do nothing
  clawSet(-43);
  wait(50);
  armSet(127);
  WaitUntilArmPot(200);
  armSet(20);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 350 && encoderGet(enc2) < 350) {
  } // do nothing
  driveSet(0, 0);
  wait(100);
  DriveRotateRightSpeed(75, 75, 0, 0);
  while (gyroGet(gyro1) < 150) {
    DriveRotateRightSpeed(67, 67, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateLeftSpeed(127, 127, 1, 50);
  encoderReset(enc1);
  encoderReset(enc2);
  wait(100);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -100 && encoderGet(enc2) > -100) {
  } // do nothing
  armSet(127);
  WaitUntilArmPot(1600);
  armSet(127);
  clawSet(127); // opening claw
  WaitUntilArmPot(2400);
  armSet(0);
  clawSet(0);
  driveSet(0, 0);
  wait(100);
  armSet(-127);
  clawSet(127);
  while (analogRead(ArmPot) > 1900) {
  } // do nothing
  clawSet(0);
  WaitUntilArmDown();
  clawSet(127);
  while (analogRead(ClawPot) > 2000) {
  } // do nothing
  clawSet(0);
  DriveBackwardSpeed(127, 127, 1, 150);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 1000 && encoderGet(enc2) < 1000) {
  } // do nothing
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3000)
    ;
  DriveBackwardSpeed(127, 127, 1, 250);
  clawSet(127);
  wait(100);
  DriveForwardSpeed(127, 127, 1, 250);
  clawSet(-127);
  while (analogRead(ClawPot) < 3250)
    ;
  clawSet(-63);
  wait(200);
  armSet(127);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveBackwardSpeed(127, 127, 0, 0);
  WaitUntilArmPot(200);
  while (encoderGet(enc1) > -300 && encoderGet(enc2) > -300) {
  } // do nothing
  armSet(127);
  WaitUntilArmPot(1600);
  clawSet(127);
  armSet(127);
  WaitUntilArmPot(2400);
  driveSet(0, 0);
  clawSet(127);
  while (analogRead(ClawPot) > 2000) {
  } // do nothing
  clawSet(0);
}

void AutoCubeRight() {
  clawSet(-127);
  while (analogRead(ClawPot) < 1000) {
  } // do nothing
  DriveForwardSpeed(127, 127, 0, 0);
  while (analogRead(LeftLIN) > 600) {
  } // Do nothing here
  clawSet(0);
  DriveBackwardSpeed(127, 127, 1, 50);
  DriveRotateLeftSpeed(75, 75, 0, 0);
  while (gyroGet(gyro1) < 68) {
    DriveRotateLeftSpeed(75, 75, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateRightSpeed(127, 127, 1, 50);
  while (analogRead(ClawPot) < 2650)
    clawSet(-127); // make it greater //closing claw
  clawSet(0);
  while (analogRead(ClawPot) > 2750)
    clawSet(127); // make it less //opening claw
  clawSet(0);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 450 && encoderGet(enc2) < 450) {
  } // do nothing
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3000) {
  } // do nothing
  clawSet(-43);
  wait(50);
  armSet(127);
  WaitUntilArmPot(200);
  armSet(20);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 350 && encoderGet(enc2) < 350) {
  } // do nothing
  driveSet(0, 0);
  wait(100);
  DriveRotateLeftSpeed(75, 75, 0, 0);
  while (gyroGet(gyro1) < 150) {
    DriveRotateLeftSpeed(67, 67, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateRightSpeed(127, 127, 1, 50);
  encoderReset(enc1);
  encoderReset(enc2);
  wait(100);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -100 && encoderGet(enc2) > -100) {
  } // do nothing
  armSet(127);
  WaitUntilArmPot(1600);
  armSet(127);
  clawSet(127); // opening claw
  WaitUntilArmPot(2400);
  armSet(0);
  clawSet(0);
  driveSet(0, 0);
  wait(100);
  armSet(-127);
  clawSet(127);
  while (analogRead(ArmPot) > 1900) {
  } // do nothing
  clawSet(0);
  WaitUntilArmDown();
  clawSet(127);
  while (analogRead(ClawPot) > 2000) {
  } // do nothing
  clawSet(0);
  DriveBackwardSpeed(127, 127, 1, 150);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 1000 && encoderGet(enc2) < 1000) {
  } // do nothing
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3000)
    ;
  DriveBackwardSpeed(127, 127, 1, 250);
  clawSet(127);
  wait(100);
  DriveForwardSpeed(127, 127, 1, 250);
  clawSet(-127);
  while (analogRead(ClawPot) < 3250)
    ;
  clawSet(-63);
  wait(200);
  armSet(127);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveBackwardSpeed(127, 127, 0, 0);
  WaitUntilArmPot(200);
  while (encoderGet(enc1) > -300 && encoderGet(enc2) > -300) {
  } // do nothing
  armSet(127);
  WaitUntilArmPot(1600);
  clawSet(127);
  armSet(127);
  WaitUntilArmPot(2400);
  driveSet(0, 0);
  clawSet(127);
  while (analogRead(ClawPot) > 2000) {
  } // do nothing
  clawSet(0);
}

void AutoHangLeft() {
  gyroReset(gyro1);
  clawSet(-127);
  DriveBackwardSpeed(40, 40, 0, 0);
  while (analogRead(ClawPot) < 3250) {
  } // do nothing
  clawSet(0);
  driveSet(0, 0);
  DriveForwardSpeed(127, 127, 0, 0);
  encoderReset(enc1);
  encoderReset(enc2);
  while (encoderGet(enc1) < 550 && encoderGet(enc2) < 550) {
  } // do nothing
  driveSet(0, 0);
  DriveBackwardSpeed(127, 127, 1, 50);
  clawSet(127);
  armSet(127);
  while (analogRead(ArmPot) < 100) {
  } // do nothing
  armSet(0);
  while (analogRead(ClawPot) > 2700) {
  } // do nothing
  clawSet(0);
  armSet(0);
  gyroGet(gyro1); // number
  while (gyroGet(gyro1) < 10) {
    DriveRotateRightSpeed(87, 87, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateLeftSpeed(127, 127, 1, 50);
  if (gyroGet(gyro1) < 44) {
    while (gyroGet(gyro1) < 44) {
      DriveRotateRightSpeed(30, 30, 0, 0);
    }
    driveSet(0, 0);
  }
  if (gyroGet(gyro1) > 46) {
    while (gyroGet(gyro1) > 46) {
      DriveRotateLeftSpeed(30, 30, 0, 0);
    }
    driveSet(0, 0);
  }
  wait(500);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -600 && encoderGet(enc2) > -600) {
  } // do nothing
  DriveBackwardSpeed(40, 40, 0, 0);
  while (digitalRead(BackLeftBUM) == 1 && digitalRead(BackRightBUM) == 1) {
  }
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3200) {
  } // do nothing
  clawSet(0);
  DriveBackwardSpeed(127, 127, 1, 100);
  armSet(127);
  WaitUntilArmPot(1425);
  armSet(127);
  WaitUntilArmPot(2850);
  armSet(15);
  clawSet(127);
  while (analogRead(ClawPot) > 1500) {
  } // do nothing
  clawSet(0);
  armSet(-127);
  while (analogRead(ArmPot) > 50) {
  } // do nothing
  armSet(-20);
  clawSet(127);
  while (analogRead(ClawPot) > 600) {
  } // do nothing
  clawSet(0);
}

void AutoHangRight() {
  gyroReset(gyro1);
  clawSet(-127);
  DriveBackwardSpeed(40, 40, 0, 0);
  while (analogRead(ClawPot) < 3250) {
  } // do nothing
  clawSet(0);
  driveSet(0, 0);
  DriveForwardSpeed(127, 127, 0, 0);
  encoderReset(enc1);
  encoderReset(enc2);
  while (encoderGet(enc1) < 550 && encoderGet(enc2) < 550) {
  } // do nothing
  driveSet(0, 0);
  DriveBackwardSpeed(127, 127, 1, 50);
  clawSet(127);
  armSet(127);
  while (analogRead(ArmPot) < 100) {
  } // do nothing
  armSet(0);
  while (analogRead(ClawPot) > 2700) {
  } // do nothing
  clawSet(0);
  armSet(0);
  gyroGet(gyro1); // number
  while (gyroGet(gyro1) > -10) {
    DriveRotateLeftSpeed(87, 87, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateRightSpeed(127, 127, 1, 50);
  if (gyroGet(gyro1) > -44) {
    while (gyroGet(gyro1) > -44) {
      DriveRotateLeftSpeed(30, 30, 0, 0);
    }
    driveSet(0, 0);
  }
  if (gyroGet(gyro1) < -46) {
    while (gyroGet(gyro1) < -46) {
      DriveRotateRightSpeed(30, 30, 0, 0);
    }
    driveSet(0, 0);
  }
  wait(500);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -600 && encoderGet(enc2) > -600) {
  } // do nothing
  DriveBackwardSpeed(40, 40, 0, 0);
  while (digitalRead(BackLeftBUM) == 1 && digitalRead(BackRightBUM) == 1) {
  }
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3200) {
  } // do nothing
  clawSet(0);
  DriveBackwardSpeed(127, 127, 1, 100);
  armSet(127);
  WaitUntilArmPot(2850);
  armSet(15);
  clawSet(127);
  while (analogRead(ClawPot) > 1500) {
  } // do nothing
  clawSet(0);
  armSet(-127);
  while (analogRead(ArmPot) > 50) {
  } // do nothing
  armSet(-20);
  clawSet(127);
  while (analogRead(ClawPot) > 600) {
  } // do nothing
  clawSet(0);
}

void UserHang() {
  armSet(127);
  WaitUntilArmPot(2850);
  armSet(15);
  clawSet(127);
  while (analogRead(ClawPot) > 1200) {
  } // do nothing
  clawSet(0);
  armSet(-127);
  while (analogRead(ArmPot) > 50) {
  } // do nothing
  armSet(-20);
  clawSet(127);
  while (analogRead(ClawPot) > 780) {
  } // do nothing
  clawSet(0);
  armSet(0);
}

void AutoUnHang() {
  clawSet(-127);
  while (analogRead(ClawPot) < 1200) {
  } // do nothing
  clawSet(0);
  armSet(127);
  WaitUntilArmPot(2850);
  armSet(15);
  clawSet(-127);
  while (analogRead(ClawPot) < 3200) {
  } // do nothing
  clawSet(0);
  armSet(0);
}

void AutoHangRight2() {
  gyroReset(gyro1);
  wait(200);
  clawSet(-127);
  while (analogRead(ClawPot) < 1900)
    ;
  clawSet(0);
  armSet(127);
  WaitUntilArmPot(300);
  while (gyroGet(gyro1) > -72) {
    DriveRotateLeftSpeed(63, 63, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateRightSpeed(127, 127, 1, 50);
  wait(200);
  clawSet(-127);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -500 && encoderGet(enc2) > -500) {
  } // do nothing
  driveSet(0, 0);
  wait(100);
  DriveBackwardSpeed(40, 40, 0, 0);
  wait(400);
  driveSet(0, 0);
  while (analogRead(ClawPot) < 3200)
    ;
  clawSet(0);
  wait(200);
  while (gyroGet(gyro1) < -45) {
    DriveRotateRightSpeed(40, 40, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateLeftSpeed(127, 127, 1, 50);
  wait(200);
  DriveBackwardSpeed(63, 63, 0, 0);
  wait(500);
  driveSet(0, 0);
  wait(200);
  while (gyroGet(gyro1) < -45)
    DriveRotateRightSpeed(40, 40, 0, 0); // turn
  while (gyroGet(gyro1) > -45)
    DriveRotateLeftSpeed(40, 40, 0, 0); // number
  while (gyroGet(gyro1) < -45)
    DriveRotateRightSpeed(40, 40, 0, 0); // 3
  driveSet(0, 0);
  wait(200);
  while (digitalRead(BackRightBUM) == 1 || digitalRead(BackLeftBUM) == 1) {
    driveSet(40, -40);
  }
  driveSet(0, 0);
  wait(200);
  armSet(127);
  WaitUntilArmPot(2850);
  armSet(15);
  clawSet(127);
  while (analogRead(ClawPot) > 1200) {
  } // do nothing
  clawSet(0);
  armSet(-127);
  while (analogRead(ArmPot) > 50) {
  } // do nothing
  armSet(-20);
  clawSet(127);
  while (analogRead(ClawPot) > 600) {
  } // do nothing
  clawSet(0);
  armSet(0);
}

void AutoHangLeft2() {
  gyroReset(gyro1);
  wait(200);
  clawSet(-127);
  while (analogRead(ClawPot) < 1900)
    ;
  clawSet(0);
  armSet(127);
  WaitUntilArmPot(300);
  while (gyroGet(gyro1) < 72) {
    DriveRotateRightSpeed(63, 63, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateLeftSpeed(127, 127, 1, 50);
  wait(200);
  clawSet(-127);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -500 && encoderGet(enc2) > -500) {
  } // do nothing
  driveSet(0, 0);
  wait(100);
  DriveBackwardSpeed(40, 40, 0, 0);
  wait(400);
  driveSet(0, 0);
  while (analogRead(ClawPot) < 3200)
    ;
  clawSet(0);
  wait(200);
  while (gyroGet(gyro1) > 45) {
    DriveRotateLeftSpeed(40, 40, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateRightSpeed(127, 127, 1, 50);
  wait(200);
  DriveBackwardSpeed(63, 63, 0, 0);
  wait(500);
  driveSet(0, 0);
  wait(200);
  while (gyroGet(gyro1) < 45)
    DriveRotateRightSpeed(40, 40, 0, 0); // turn
  while (gyroGet(gyro1) > 46)
    DriveRotateLeftSpeed(40, 40, 0, 0); // number
  while (gyroGet(gyro1) < 45)
    DriveRotateRightSpeed(40, 40, 0, 0); // 3
  driveSet(0, 0);
  wait(200);
  while (digitalRead(BackRightBUM) == 1 || digitalRead(BackLeftBUM) == 1) {
    driveSet(40, -40);
  }
  driveSet(0, 0);
  wait(200);
  armSet(127);
  WaitUntilArmPot(2850);
  armSet(15);
  clawSet(127);
  while (analogRead(ClawPot) > 1200) {
  } // do nothing
  clawSet(0);
  armSet(-127);
  while (analogRead(ArmPot) > 50) {
  } // do nothing
  armSet(-20);
  clawSet(127);
  while (analogRead(ClawPot) > 600) {
  } // do nothing
  clawSet(0);
  armSet(0);
}

void LCDConfiguration() {}

void Programming_Skills() {
  gyroReset(gyro1);
  clawSet(-127);
  DriveBackwardSpeed(127, 127, 0, 0);
  wait(600);
  while (analogRead(LeftLIN) > 600) {
  } // Do nothing here
  DriveForwardSpeed(127, 127, 1, 50);
  clawSet(0);
  wait(500);
  clawSet(-127);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 75 && encoderGet(enc2) < 75) {
  } // do nothing
  driveSet(0, 0);
  while (analogRead(ClawPot) < 3025) {
  } // do nothing
  clawSet(-90);
  wait(200);
  armSet(127);
  WaitUntilArmPot(200);
  encoderReset(enc1);
  encoderReset(enc2);
  wait(200);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -100 && encoderGet(enc2) > -100) {
  } // do nothing
  armSet(127);
  WaitUntilArmPot(1600);
  armSet(127);
  clawSet(127); // opening claw
  WaitUntilArmPot(2400);
  armSet(0);
  clawSet(0);
  driveSet(0, 0);

  // start section 1b

  armSet(-127);
  WaitUntilArmDown();
  DriveBackwardSpeed(127, 127, 1, 300);
  clawSet(127);
  while (analogRead(ClawPot) > 2750) {
  } // do nothing
  clawSet(0);
  DriveForwardSpeed(127, 127, 0, 0);
  while (analogRead(LeftLIN) > 600) {
  } // do nothing
  driveSet(0, 0);
  wait(200);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 25 && encoderGet(enc2) < 25) {
  } // do nothing
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3025) {
  } // do nothing
  clawSet(-90);
  wait(500);
  armSet(127);
  WaitUntilArmPot(200);
  encoderReset(enc1);
  encoderReset(enc2);
  wait(200);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -100 && encoderGet(enc2) > -100) {
  } // do nothing
  armSet(127);
  WaitUntilArmPot(1600);
  armSet(127);
  clawSet(127); // opening claw
  WaitUntilArmPot(2400);
  armSet(0);
  clawSet(0);
  driveSet(0, 0);

  // start section 2

  armSet(-127);
  WaitUntilArmDown();
  DriveBackwardSpeed(127, 127, 1, 300);
  DriveForwardSpeed(127, 127, 0, 0);
  while (analogRead(LeftLIN) > 600) {
  } // Do nothing here
  DriveBackwardSpeed(127, 127, 1, 50);
  wait(200);
  armSet(127);
  WaitUntilArmPot(200);
  while (analogRead(ClawPot) < 2750) {
    clawSet(-127);
  } // make it greater //closing claw
  clawSet(0);
  while (analogRead(ClawPot) > 2800) {
    clawSet(127);
  } // make it less //opening claw
  clawSet(0);
  while (gyroGet(gyro1) > -68) {
    DriveRotateLeftSpeed(80, 80, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateRightSpeed(127, 127, 1, 50);
  while (analogRead(ClawPot) < 2650) {
    clawSet(-127);
  } // make it greater //closing claw
  clawSet(0);
  while (analogRead(ClawPot) > 2750) {
    clawSet(127);
  } // make it less //opening claw
  clawSet(0);
  armSet(-127);
  WaitUntilArmDown();
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 550 && encoderGet(enc2) < 550) {
  } // do nothing
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3050) {
  } // do nothing
  clawSet(-63);
  wait(50);
  armSet(127);
  WaitUntilArmPot(500);
  armSet(20);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 1700 && encoderGet(enc2) < 1700) {
  } // do nothing
  driveSet(0, 0);
  wait(100);
  DriveRotateRightSpeed(75, 75, 0, 0);
  while (gyroGet(gyro1) < -30) {
    DriveRotateRightSpeed(67, 67, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateLeftSpeed(127, 127, 1, 50);
  encoderReset(enc1);
  encoderReset(enc2);
  wait(100);
  DriveBackwardSpeed(127, 127, 0, 0);
  armSet(127);
  WaitUntilArmPot(1600);
  armSet(127);
  clawSet(127); // opening claw
  WaitUntilArmPot(2400);
  armSet(0);
  clawSet(0);
  driveSet(0, 0);

  // start section 3

  armSet(-127);
  WaitUntilArmDown();
  clawSet(127);
  while(analogRead(ClawPot) > 1800) {} //do nothing
  clawSet(0);
  DriveForwardSpeed(127, 127, 0, 0);
  while (analogRead(LeftLIN) > 600) {
  } // do nothing
  driveSet(0, 0);
  wait(200);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveForwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) < 25 && encoderGet(enc2) < 25) {
  } // do nothing
  driveSet(0, 0);
  clawSet(-127);
  while (analogRead(ClawPot) < 3025) {
  } // do nothing
  clawSet(-90);
  wait(500);
  armSet(127);
  WaitUntilArmPot(200);
  encoderReset(enc1);
  encoderReset(enc2);
  wait(200);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -100 && encoderGet(enc2) > -100) {
  } // do nothing
  armSet(127);
  WaitUntilArmPot(1600);
  armSet(127);
  clawSet(127); // opening claw
  WaitUntilArmPot(2400);
  armSet(0);
  clawSet(0);
  driveSet(0, 0);

  //section 4

  armSet(-127);
  while(analogRead(ArmPot) > 1500) {} //do nothing
  armSet(0);
  DriveBackwardSpeed(127, 127, 1, 300);
  DriveForwardSpeed(127, 127, 0, 0);
  while(analogRead(LeftLIN) > 600) {} //do nothing
  DriveForwardSpeed(127, 127, 1, 1500);
  gyroReset(gyro1);
  while (gyroGet(gyro1) < 72) {
    DriveRotateRightSpeed(63, 63, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateLeftSpeed(127, 127, 1, 50);
  clawSet(-127);
  encoderReset(enc1);
  encoderReset(enc2);
  DriveBackwardSpeed(127, 127, 0, 0);
  while (encoderGet(enc1) > -500 && encoderGet(enc2) > -500) {
  } // do nothing
  driveSet(0, 0);
  wait(100);
  DriveBackwardSpeed(40, 40, 0, 0);
  wait(700);
  driveSet(0, 0);
  while (analogRead(ClawPot) < 3200);
  clawSet(0);
  wait(200);
  while (gyroGet(gyro1) > 135) {
    DriveRotateLeftSpeed(40, 40, 0, 0);
  }
  driveSet(0, 0);
  DriveRotateLeftSpeed(127, 127, 1, 50);
  wait(200);
  DriveBackwardSpeed(63, 63, 0, 0);
  wait(500);
  driveSet(0, 0);
  wait(200);
  while (gyroGet(gyro1) < 135)
    DriveRotateRightSpeed(40, 40, 0, 0); // turn
  while (gyroGet(gyro1) > 135)
    DriveRotateLeftSpeed(40, 40, 0, 0); // number
  while (gyroGet(gyro1) < 135)
    DriveRotateRightSpeed(40, 40, 0, 0); // 3
  driveSet(0, 0);
  wait(200);
  while (digitalRead(BackRightBUM) == 1 || digitalRead(BackLeftBUM) == 1) {
    driveSet(40, -40);
  }
  driveSet(0, 0);
  wait(200);
  armSet(127);
  WaitUntilArmPot(2850);
  armSet(15);
  clawSet(127);
  while (analogRead(ClawPot) > 1200) {
  } // do nothing
  clawSet(0);
  armSet(-127);
  while (analogRead(ArmPot) > 50) {
  } // do nothing
  armSet(-20);
  clawSet(127);
  while (analogRead(ClawPot) > 600) {
  } // do nothing
  clawSet(0);
  armSet(0);

  }

  void ProgrammingMap() {
    DriveForwardSpeed(127, 127, 0, 0);
    wait(200);
    while (analogRead(LeftLIN) > 600) {
    } // Do nothing here
    DriveBackwardSpeed(127, 127, 1, 50);
    wait(200);
    while (gyroGet(gyro1) < 68) {
      DriveRotateRightSpeed(127, 127, 0, 0);
    }
    driveSet(0, 0);
    DriveRotateLeftSpeed(127, 127, 1, 50);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 520 && encoderGet(enc2) < 520) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -560 && encoderGet(enc2) > -560) {
    } // do nothing
    driveSet(0, 0);
    wait(200);
    DriveRotateRightSpeed(127, 127, 0, 0);
    while (gyroGet(gyro1) < 162) {
      DriveRotateRightSpeed(127, 127, 0, 0);
    }
    driveSet(0, 0);
    DriveRotateLeftSpeed(127, 127, 1, 50);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -100 && encoderGet(enc2) > -100) {
    } // do nothing
    while (encoderGet(enc1) > -540 && encoderGet(enc2) > -540) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -200 && encoderGet(enc2) > -200) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);

    // start section 2
    // start section 2a
    DriveForwardSpeed(127, 127, 0, 0);
    while (analogRead(LeftLIN) > 600) {
    }
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 900 && encoderGet(enc2) < 900) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -500 && encoderGet(enc2) > -500) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    while (encoderGet(enc1) > -300 && encoderGet(enc2) > -300) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -150 && encoderGet(enc2) > -150) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    wait(200);
    // start section 2b
    DriveForwardSpeed(127, 127, 0, 0);
    while (analogRead(LeftLIN) > 600) {
    }
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 900 && encoderGet(enc2) < 900) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -500 && encoderGet(enc2) > -500) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    while (encoderGet(enc1) > -300 && encoderGet(enc2) > -300) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -150 && encoderGet(enc2) > -150) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    wait(200);

    // start section 3
    gyroReset(gyro1);
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 400 && encoderGet(enc2) < 400) {
    } // do nothing
    driveSet(0, 0);
    wait(200);
    DriveRotateLeftSpeed(127, 127, 0, 0);
    while (gyroGet(gyro1) > -68) {
      DriveRotateLeftSpeed(127, 127, 0, 0);
    }
    driveSet(0, 0);
    DriveRotateRightSpeed(127, 127, 1, 50);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 1000 && encoderGet(enc2) < 1000) {
    } // do nothing
    driveSet(0, 0);
    wait(200);
    DriveRotateRightSpeed(127, 127, 0, 0);
    while (gyroGet(gyro1) < -22) {
      DriveRotateRightSpeed(127, 127, 0, 0);
    }
    driveSet(0, 0);
    DriveRotateLeftSpeed(127, 127, 1, 50);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 200 && encoderGet(enc2) < 200) {
    } // do nothing
    driveSet(0, 0);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -150 && encoderGet(enc2) > -150) {
    } // do nothing
    while (encoderGet(enc1) > -400 && encoderGet(enc2) > -400) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -400 && encoderGet(enc2) > -400) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    wait(200);
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 900 && encoderGet(enc2) < 900) {
    } // do nothing
    driveSet(0, 0);
    encoderReset(enc1);
    encoderReset(enc2);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -500 && encoderGet(enc2) > -500) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    while (encoderGet(enc1) > -300 && encoderGet(enc2) > -300) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -150 && encoderGet(enc2) > -15) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    driveSet(0, 0);
    wait(200);
    // start section 4
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 530 && encoderGet(enc2) < 530) {
    } // do nothing
    driveSet(0, 0);
    wait(200);
    DriveRotateLeftSpeed(127, 127, 0, 0);
    while (gyroGet(gyro1) > -68) {
      DriveRotateLeftSpeed(127, 127, 0, 0);
    }
    driveSet(0, 0);
    DriveRotateRightSpeed(127, 127, 1, 50);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 1250 && encoderGet(enc2) < 1250) {
    } // do nothing
    driveSet(0, 0);
    wait(200);
    DriveRotateRightSpeed(127, 127, 0, 0);
    while (gyroGet(gyro1) < -22) {
      DriveRotateRightSpeed(127, 127, 0, 0);
    }
    driveSet(0, 0);
    DriveRotateLeftSpeed(127, 127, 1, 50);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 680 && encoderGet(enc2) < 680) {
    } // do nothing
    driveSet(0, 0);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -600 && encoderGet(enc2) > -600) {
    } // do nothing
    while (encoderGet(enc1) > -900 && encoderGet(enc2) > -900) {
    } // do nothing
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveForwardSpeed(127, 127, 0, 0);
    while (analogRead(LeftLIN) > 600) {
    }
    driveSet(0, 0);
    wait(200);
    DriveRotateRightSpeed(127, 127, 0, 0);
    while (gyroGet(gyro1) < 68) {
      DriveRotateRightSpeed(127, 127, 0, 0);
    }
    driveSet(0, 0);
    DriveRotateLeftSpeed(127, 127, 1, 50);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -900 && encoderGet(enc2) > -900) {
    } // do nothing
    driveSet(0, 0);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveForwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) < 900 && encoderGet(enc2) < 900) {
    } // do nothing
    while (gyroGet(gyro1) < 124) {
      DriveRotateRightSpeed(127, 127, 0, 0);
    }
    driveSet(0, 0);
    DriveRotateLeftSpeed(127, 127, 1, 50);
    encoderReset(enc1);
    encoderReset(enc2);
    wait(200);
    DriveBackwardSpeed(127, 127, 0, 0);
    while (encoderGet(enc1) > -1500 && encoderGet(enc2) > -1500) {
    } // do nothing
  }

  void AutonSelection() {
    if (analogRead(AutoPot) > 3900) {
      FollowInstructions();
    } // 1
    if (analogRead(AutoPot) > 3200 && analogRead(AutoPot) < 3600) {
      AutoCubeLeft();
    } // 1
    if (analogRead(AutoPot) > 2500 && analogRead(AutoPot) < 2900) {
      AutoHangLeft2();
    } // 1
    if (analogRead(AutoPot) > 1600 && analogRead(AutoPot) < 2000) {
      Programming_Skills();
    } // Programming Skills
    if (analogRead(AutoPot) > 1000 && analogRead(AutoPot) < 1400) {
      AutoHangRight2();
    } // 2
    if (analogRead(AutoPot) > 300 && analogRead(AutoPot) < 700) {
      AutoCubeRight();
    } // 2
  }
