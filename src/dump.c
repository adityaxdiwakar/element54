/*
clawSet(-127);
wait(100);
armSet(127);
WaitUntilArmPot(1000);
armSet(-127);
WaitUntilArmDown();
clawSet(0);
DriveForwardSpeed(127, 127, 0, 0);
wait(200);
while(analogRead(LeftLIN) > 600) {} //Do nothing here
DriveBackwardSpeed(127, 127, 1, 50);
while(gyroGet(gyro1) < 68) {
  DriveRotateRightSpeed(127, 127, 0, 0); }
driveSet(0, 0);
DriveRotateLeftSpeed(127, 127, 1, 50);
DriveForwardSpeed(127, 127, 1, 700);
clawSet(-127);
wait(600);
armSet(127);
DriveBackwardSpeed(127, 127, 0, 0);
WaitUntilArmPot(1000);
armSet(20);
wait(400);
DriveRotateRightSpeed(127, 127, 0, 0);
while(gyroGet(gyro1) < 162) {
  DriveRotateRightSpeed(127, 127, 0, 0); }
driveSet(0, 0);
DriveRotateLeftSpeed(127, 127, 1, 50);
DriveBackwardSpeed(127, 127, 0, 0);
wait(500);
armSet(127);
while(analogRead(ArmPot) < 1555) {}
clawSet(127);
WaitUntilArmVert();
armSet(127);
wait(150);
armSet(0);
clawSet(0);
//end section
//start section 2a
clawSet(-127);
armSet(-127);
WaitUntilArmStable();
clawSet(0);
wait(100);
driveSet(0,0);
armSet(-127);
WaitUntilArmDown();
DriveForwardSpeed(127, 127, 0, 0);
clawSet(127);
wait(100);
clawSet(0);
DriveForwardSpeed(127, 127, 0, 0);
while(analogRead(LeftLIN) > 600) {}
clawSet(0);
DriveForwardSpeed(127, 127, 1, 50);
clawSet(-127);
wait(1000);
armSet(127);
DriveBackwardSpeed(127, 127, 0, 0);
WaitUntilArmPot(400);
armSet(20);
wait(300);
armSet(127);
while(analogRead(ArmPot) < 1555) {}
clawSet(127);
WaitUntilArmVert();
armSet(127);
wait(200);
armSet(0);
clawSet(0);
driveSet(0, 0); //end section 2a
//start section 2b
clawSet(-127);
armSet(-127);
WaitUntilArmStable();
clawSet(0);
wait(100);
driveSet(0,0);
armSet(-127);
WaitUntilArmDown();
DriveForwardSpeed(127, 127, 0, 0);
clawSet(127);
wait(100);
clawSet(0);
DriveForwardSpeed(127, 127, 0, 0);
while(analogRead(LeftLIN) > 600) {}
clawSet(0);
DriveForwardSpeed(127, 127, 1, 50);
clawSet(-127);
wait(1000);
armSet(127);
DriveBackwardSpeed(127, 127, 0, 0);
WaitUntilArmPot(400);
armSet(20);
wait(300);
armSet(127);
while(analogRead(ArmPot) < 1555) {}
clawSet(127);
WaitUntilArmVert();
armSet(127);
wait(200);
armSet(0);
clawSet(0);
driveSet(0,0); //end section 2
armSet(-127);
while(analogRead(ArmPot) > 1555) {} //do nothing
armSet(0);
WaitUntilArmStable();
DriveBackwardSpeed(127, 127, 1, 350);
driveSet(0, 0);
armSet(-127);
WaitUntilArmDown();
DriveForwardSpeed(127, 127, 1, 700);
DriveRotateLeftSpeed(127, 127, 0, 0);
while(gyroGet(gyro1) > 115) {
  DriveRotateLeftSpeed(127, 127, 0, 0); }
driveSet(0, 0);
DriveRotateRightSpeed(127, 127, 1, 50);
DriveForwardSpeed(127, 127, 1, 1500);
clawSet(-127);
while(analogRead(ClawPot) > 45) {}
wait(500);
DriveBackwardSpeed(127, 127, 1, 300);
DriveRotateRightSpeed(127, 127, 1, 250);
armSet(127);
WaitUntilArmPot(400);
armSet(15);
DriveRotateRightSpeed(127, 127, 0, 0);
while(gyroGet(gyro1) < 162) {
DriveRotateRightSpeed(127, 127, 0, 0); }
driveSet(0, 0);
DriveRotateLeftSpeed(127, 127, 1, 50);
armSet(15);
DriveForwardSpeed(127, 127, 1, 300);
DriveBackwardSpeed(127, 127, 0, 0);
wait(200);
armSet(127);
WaitUntilArmStable();
armSet(127);
clawSet(127);
WaitUntilArmVert();
armSet(127);
wait(200);
armSet(0);
driveSet(0, 0); //end section 3
clawSet(-127);
armSet(-127);
WaitUntilArmStable();
clawSet(0);
wait(100);
driveSet(0,0);
armSet(-127);
WaitUntilArmDown();
DriveForwardSpeed(127, 127, 0, 0);
clawSet(127);
wait(100);
clawSet(0);
DriveForwardSpeed(127, 127, 0, 0);
while(analogRead(LeftLIN) > 600) {}
clawSet(0);
DriveForwardSpeed(127, 127, 1, 50);
clawSet(-127);
wait(1000);
DriveBackwardSpeed(127, 127, 1, 250);
clawSet(127);
DriveForwardSpeed(127, 127, 1, 150);
clawSet(-127);
wait(500);
armSet(127);
DriveBackwardSpeed(127, 127, 0, 0);
WaitUntilArmPot(400);
armSet(20);
wait(300);
armSet(127);
while(analogRead(ArmPot) < 1555) {}
clawSet(127);
WaitUntilArmVert();
armSet(127);
wait(200);
armSet(0);
clawSet(0);
driveSet(0, 0);  //end section 4
*/


//2

/*  if(joystickGetDigital(1,7,JOY_UP)) {
  clawSet(-127);
  while(analogRead(ClawPot) < 3150) {} //do nothing
  clawSet(-40);
  wait(50);
  armSet(127);
  WaitUntilArmPot(200);
  armSet(20);
  wait(2000);
  armSet(127);
  WaitUntilArmPot(1600);
  armSet(127);
  clawSet(127); //opening claw
  WaitUntilArmPot(2400);
  armSet(0);
  clawSet(0);*/



//3

/*
while(1) {printf("Claw is %d\n", analogRead(ArmPot));}
if(joystickGetDigital(1,7,JOY_UP)) {
  clawSet(-127);
  while(analogRead(ClawPot) < 3100) {} //do nothing
  printf("Arm before is %d\n", analogRead(ArmPot));
  lcdPrint(uart1, 1, "Arm is %d", analogRead(ArmPot));
  armSet(127);
  while(analogRead(ClawPot) > 2800) { clawSet(127); }
  armSet(0);
  clawSet(0);
  printf("Arm after is %d\n", analogRead(ArmPot));
  lcdPrint(uart1, 2, "Arm is %d", analogRead(ArmPot));
}


//4

/*    if(joystickGetDigital(1,7,JOY_UP)) {
        encoderReset(enc1);
        encoderReset(enc2);
        armSet(127);
        WaitUntilArmPot(400);
        armSet(127);
        DriveBackwardSpeed(127, 127, 0, 0);
        WaitUntilArmPot(1100);
        driveSet(0,0);
      }*/


      /*
      DriveBackwardSpeed(127, 127, 0, 0);
      clawSet(-127);
      while(analogRead(LeftLIN) > 600) {} //Do nothing here
      encoderReset(enc1);
      encoderReset(enc2);
      DriveBackwardSpeed(127, 127, 0, 0);
      while(encoderGet(enc1) > -200 && encoderGet(enc2) > -200) {} //do nothing
      driveSet(0,0);
      while(analogRead(ClawPot) < 1700) {} //do nothing
      clawSet(0);
      armSet(127);
      WaitUntilArmPot(2700);
      armSet(-15);
      wait(1000);
      DriveBackwardSpeed(127, 127, 1, 400);
      DriveForwardSpeed(63, 63, 1, 300);
      armSet(-127);
      WaitUntilArmDown();
      DriveForwardSpeed(127, 127, 0, 0);
      while(analogRead(LeftLIN) > 600) {} //Do nothing here*/

      /*
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
      while (gyroGet(gyro1) > -100) {
        DriveRotateLeftSpeed(85, 85, 0, 0);
      }
      driveSet(0, 0);
      DriveRotateRightSpeed(127, 127, 1, 50);
      armSet(-127);
      WaitUntilArmDown();
      encoderReset(enc1);
      encoderReset(enc2);
      DriveForwardSpeed(127, 127, 0, 0);
      while (encoderGet(enc1) < 300 && encoderGet(enc2) < 300) {
      } // do nothing
      while (gyroGet(gyro1) < -105) {
        DriveRotateRightSpeed(85, 85, 0, 0); }
      encoderReset(enc1);
      encoderReset(enc2);
      DriveForwardSpeed(127, 127, 0, 0);
      while (encoderGet(enc1) < 200 && encoderGet(enc2) < 200) {
      } // do nothing
      while (gyroGet(gyro1) < -90) {
        DriveRotateRightSpeed(85, 85, 0, 0); }
      encoderReset(enc1);
      encoderReset(enc2);
      DriveForwardSpeed(127, 127, 0, 0);
      while (encoderGet(enc1) < 200 && encoderGet(enc2) < 200) {} //do nothing
      driveSet(0,0);
      clawSet(-127);
      while (analogRead(ClawPot) < 3100) {} //do nothing
      clawSet(-90);
      wait(200);
      armSet(127);
      WaitUntilArmPot(500);
      encoderReset(enc1);
      encoderReset(enc2);
      DriveForwardSpeed(127, 127, 0, 0);
      while (encoderGet(enc1) < 600 && encoderGet(enc2) < 600) {} //do nothing
      while (gyroGet(gyro1) < -22) {
        DriveRotateRightSpeed(85, 85, 0, 0);
      }
      driveSet(0, 0);
      DriveBackwardSpeed(127, 127, 0, 0);
      armSet(127);
      WaitUntilArmPot(1600);
      armSet(127);
      clawSet(127); // opening claw
      WaitUntilArmPot(2400);
      armSet(0);
      clawSet(0);
      driveSet(0, 0);*/
