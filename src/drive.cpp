
#include "../include/drive.hpp"
#include "../include/sensors.hpp"
#include "../include/joystick.hpp"
#include "cmath"

namespace drive {

  bool driveConstant = true;
  motors frontLeft;
  motors frontRight;
  motors backLeft;
  motors backRight;

  void init(int motorNum, bool isReverse, bool isTruespeed, char location[]) {
    if (location == "frontLeft") {
      frontLeft.motorNum = motorNum;
      frontLeft.isReverse = isReverse;
      frontLeft.isTruespeed = isTruespeed;
    } else if (location == "frontRight") {
      frontRight.motorNum = motorNum;
      frontRight.isReverse = isReverse;
      frontRight.isTruespeed = isTruespeed;
    } else if (location == "backRight") {
      backRight.motorNum = motorNum;
      backRight.isReverse = isReverse;
      backRight.isTruespeed = isTruespeed;
    } else if (location == "backLeft") {
      backLeft.motorNum = motorNum;
      backLeft.isReverse = isReverse;
      backLeft.isTruespeed = isTruespeed;
    }
  }

  //truespeed mappings
  int MC29[128] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    13,
    13,
    14,
    14,
    14,
    14,
    15,
    15,
    15,
    15,
    16,
    16,
    16,
    16,
    16,
    17,
    17,
    17,
    17,
    17,
    17,
    17,
    17,
    18,
    18,
    18,
    18,
    18,
    18,
    18,
    19,
    19,
    19,
    19,
    19,
    20,
    20,
    20,
    20,
    21,
    21,
    21,
    22,
    22,
    22,
    22,
    23,
    23,
    23,
    23,
    24,
    24,
    24,
    25,
    25,
    25,
    26,
    26,
    26,
    27,
    27,
    27,
    28,
    28,
    28,
    29,
    29,
    30,
    30,
    30,
    31,
    31,
    32,
    32,
    33,
    33,
    34,
    34,
    35,
    36,
    36,
    37,
    37,
    38,
    39,
    40,
    40,
    41,
    42,
    43,
    44,
    45,
    46,
    46,
    48,
    49,
    50,
    51,
    53,
    55,
    56,
    58,
    60,
    62,
    64,
    67,
    70,
    72,
    76,
    79,
    83,
    84,
    127,
  };

  int sgn(int x, int max = 127) {
    if (x > max) {
      return (max);
    } else return (x);
  }

  void trueSpeed(int iPort, int iSpeed) {
    if(iSpeed < 25 && iSpeed > 0) iSpeed = 0;
    if(iSpeed > -25 && iSpeed < 0) iSpeed = 0;
    if (iSpeed > 0) {
      motorSet(iPort, MC29[sgn(abs(iSpeed))]);
    } else if (iSpeed < 0) {
      motorSet(iPort, -(MC29[sgn(abs(iSpeed))]));
    } else {
      motorSet(iPort, 0);
    }
  }

  void left(int iSpeed) {
    if(driveConstant) {
     iSpeed = iSpeed < 25 && iSpeed > 0 ? 0 : (iSpeed > -25 && iSpeed < 0 ? 0 : iSpeed);
    }
    motorSet(frontLeft.motorNum, iSpeed * frontLeft.isReverse);
    motorSet(backLeft.motorNum, iSpeed * backLeft.isReverse);
  }

  void right(int iSpeed) {
    if(driveConstant) {
     iSpeed = iSpeed < 25 && iSpeed > 0 ? 0 : (iSpeed > -25 && iSpeed < 0 ? 0 : iSpeed);
    }
    motorSet(frontRight.motorNum, -iSpeed);
    motorSet(backRight.motorNum, iSpeed * backRight.isReverse);
  }

  void speed(int iSpeed) {
    left(iSpeed);
    right(iSpeed);
  }
  void timed(int iSpeed, int duration) {
    speed(iSpeed);
    delay(duration);
    speed(0);
  }

    using namespace std;
    pid sDrivePID;
    int
    iDrivePID( int target ) {
    sDrivePID.kP = .2;
    sDrivePID.kD = 1;
    sDrivePID.current = sensors::drive::get();
    sDrivePID.error = target - sDrivePID.current;
    sDrivePID.derivative = sDrivePID.error - sDrivePID.lastError;
    sDrivePID.lastError = sDrivePID.error;
    return ( (sDrivePID.error * sDrivePID.kP) + (sDrivePID.derivative *sDrivePID.kD) + (15 * (sDrivePID.error / abs(sDrivePID.error) ) ) );
    }

    pid sRotatePID;
    int iRotatePID( int target) {
    sRotatePID.kP = 9;
    sRotatePID.kD = 6;
    sRotatePID.kI = 0; 
    sRotatePID.current = sensors::gyro::get();
    sRotatePID.error = target - sRotatePID.current;
    sRotatePID.integral += sRotatePID.error;  
    sRotatePID.derivative = sRotatePID.error - sRotatePID.lastError;
    sRotatePID.lastError = sRotatePID.error;
    return ( (sRotatePID.error * sRotatePID.kP)+ (sRotatePID.derivative * sRotatePID.kD) + (sRotatePID.integral * sRotatePID.kI) + 15 *(sRotatePID.error/(abs(sRotatePID.error))));
    }


  void vDrive(void*parameter) {
      while(true) {
          speed(iDrivePID(((int)parameter)));
      }
  }

  void vRotate(void*parameter) {
      while(true) {
          right(iRotatePID(((int)parameter)));
          left(-iRotatePID(((int)parameter)));
      }
  }

  void autoDrive(void * parameter) {
    sensors::drive::reset();

    int sp = (int) parameter;
    //PD variables
    double kp = 0.19;
    double kd = 0;
    int prevError = 0;

    int kc = 30;
    int brake = 20;
    int dir = 1; //forward
    if (sp < 0) { //backward
      dir = 0;
      brake = -brake;
    }

    while (1) {
      int sv         = sensors::drive::get();
      int error      = sp - sv;
      int derivative = error - prevError;
      int v          = error * kp + derivative * kd;
      prevError      = error;

      //v normalization
      if (dir == 1 && v < kc) v = kc;
      if (dir == 0 && v > -kc) v = -kc;

      speed(v);

      if (dir == 0 && error > 0) break;
      if (dir == 1 && error < 0) break;
      delay(20);
    }
    speed(-brake);
    delay(50);
    speed(0); // stop drive
    taskDelete(NULL);
  }

  void gyTurn(void *parameter) {
    int sp = (int)parameter;
    float kp = 1.225;
    if (abs(sp - sensors::gyro::get() > 110)) kp = 1.225;
    if (abs(sp - sensors::gyro::get() > 150)) kp = 1.225;
    if (abs(sp - sensors::gyro::get() > 180)) kp = 1.225;
    int kc = 45;
    int brake = 50;

    //set direction
    int dir = 0; //left
    if (sp - sensors::gyro::get() < 0) dir = 1;
    if (dir == 1) brake = -brake;

    while (1) {
      int sv = sensors::gyro::get(); // get sensor

      //calculate speed
      int error = sp - sv;
      int speed = error * kp;

      //velocity normalization
      if (speed > 127) speed = 127;
      if (speed < -127) speed = -127;

      //kc enforcement
      if (dir == 0 && speed < kc) speed = kc;
      if (dir == 1 && speed > -kc) speed = -kc;

      //end loop check
      if (dir == 0 && error <= 0) break;
      if (dir == 1 && error >= 0) break;

      left(-speed);
      right(speed);

      delay(20);
    }
    left(brake);
    right(-brake);
    delay(100);
    speed(0); // stop drive
    taskDelete(NULL);
  }
  namespace teleop {
    unsigned long cycleTime;
    void arcade(int speed, int turn) {
      //speed = speed - joyInit.defaultY;
      //turn = turn - joyInit.defaultX;
      speed = !driveConstant ? (speed + 13) : speed;
      left(speed + turn);
      right(speed - turn);
      if(joystick::digital(8, joystick::Left) && (millis() - cycleTime) > 250) {
        driveConstant = !driveConstant;
        cycleTime = millis();
      }
    }
  }
}

