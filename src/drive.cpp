#include "../include/drive.hpp"
#include "../include/sensors.hpp"

namespace drive {
    motors frontLeft;
    motors frontRight;
    motors backLeft;
    motors backRight;

    void init(int motorNum, int isReverse, bool isTruespeed, char location[]) {
        if(location == "frontLeft") {
            frontLeft.motorNum = motorNum;
            frontLeft.isReverse = isReverse;
            frontLeft.isTruespeed = isTruespeed;
        } else if(location == "frontRight") {
            frontRight.motorNum = motorNum;
            frontRight.isReverse = isReverse;
            frontRight.isTruespeed = isTruespeed;
        } else if(location == "backRight") {
            backRight.motorNum = motorNum;
            backRight.isReverse = isReverse;
            backRight.isTruespeed = isTruespeed;
        } else if(location == "backLeft") {
            backLeft.motorNum = motorNum;
            backLeft.isReverse = isReverse;
            backLeft.isTruespeed = isTruespeed;
        }
    }

    int sgn(int iSpeed) {
        if(iSpeed > 127) {
            return 127;
        }
        else {
            return iSpeed;
        }
    }

    //truespeed mappings
    int MC29[ 128 ] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 13, 13, 14,
	14, 14, 14, 15, 15, 15, 15, 16, 16, 16,
	16, 16, 17, 17, 17, 17, 17, 17, 17, 17,
	18, 18, 18, 18, 18, 18, 18, 19, 19, 19,
	19, 19, 20, 20, 20, 20, 21, 21, 21, 22,
	22, 22, 22, 23, 23, 23, 23, 24, 24, 24,
	25, 25, 25, 26, 26, 26, 27, 27, 27, 28,
	28, 28, 29, 29, 30, 30, 30, 31, 31, 32,
	32, 33, 33, 34, 34, 35, 36, 36, 37, 37,
	38, 39, 40, 40, 41, 42, 43, 44, 45, 46,
	46, 48, 49, 50, 51, 53, 55, 56, 58, 60,
	62, 64, 67, 70, 72, 76, 79, 83, 84, 127,
    };  

    void trueSpeed(int iPort, int iSpeed) {
        if(iSpeed >= 0) {
            motorSet(iPort, MC29[abs(sgn(iSpeed))]);
        }
        else if(iSpeed < 0) {
            motorSet(iPort, -(MC29[abs(sgn(iSpeed))]));
        }
    }

    void left(int iSpeed) {
        motorSet(frontLeft.motorNum, (iSpeed * frontLeft.isReverse));
        motorSet(backLeft.motorNum, (iSpeed * backLeft.isReverse));
    }

    void right(int iSpeed) {
        motorSet(frontRight.motorNum, (iSpeed * frontRight.isReverse));
        motorSet(backRight.motorNum, (iSpeed * backRight.isReverse));
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
    void waitUntil(int iSpeed, int target, bool reset) {
        if(reset) sensors::drive::reset();
        speed(iSpeed);
        if(sensors::drive::right::get() > target) {
            while(sensors::drive::right::get() > target) {
                delay(15);
            }
        }
        else if(sensors::drive::right::get() < target) {
            while(sensors::drive::right::get() < target) {
                delay(15);
            }
        }
        speed(0);
    } 


    namespace auton {
        void pid(int distance) {
            sensors::drive::reset();
            
            double kp = 0.5;
            int kc = 60;
            int brake = -60;
            int dir = 1;
            if(distance<0) {
                dir = 0;
                brake = -brake; }

            while(true) {
                int current = sensors::drive::right::get();
                int error = distance - current;
                int vel = error * kp;

                //normalize vel
                if(dir == 1 && vel < kc) vel = kc;
                if(dir == 0 && vel > kc) vel = -kc;

                speed(vel);

                if(dir == 0 && error > 0) break;
                if(dir == 1 && error < 0) break; 
                delay(20); }
            speed(brake);
            delay(200);
            speed(0);
        }
        void gyTurn(int heading, bool reset) {
            if(reset) sensors::gyro::reset();

            double kp = 3.5;
            if(abs(heading - sensors::gyro::get() > 110)) kp = 1.8;
            if(abs(heading - sensors::gyro::get() > 150)) kp = 1.2;
            int kc = 60;
            int brake = 60;
            int dir = 0;
            if(heading - sensors::gyro::get() < 0) {
                dir = 1;
                brake = -brake;
            }

            while(true) {
                int current = sensors::gyro::get();
                int error = heading - current;
                int vel = error*kp;

                
                if(vel > 127) vel = 127;
                if(vel < -127) vel = -127;

                if(dir == 0 && vel < kc) vel = kc;
                if(dir == 1 && vel > -kc) vel = -kc;

                if(dir == 0 && error <= 0) break;
                if(dir == 1 && error >= 0) break;

                left(-vel);
                right(vel);
                delay(20);
            }               
            left(brake);
            right(-brake);
            delay(100);
            speed(0);
        }
    }

    namespace teleop {
        void arcade(int speed, int turn) {
            left(speed + turn);
            right(speed - turn);
        }
    }
    }
