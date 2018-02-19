#include "../include/drive.hpp"

namespace drive {
    motors frontLeft;
    motors frontRight;
    motors backLeft;
    motors backRight;

    void init(int motorNum, bool isReverse, bool isTruespeed, char location[]) {
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
        if(iSpeed > 0) {
            motorSet(iPort, MC29[iSpeed]);
        }
        else if(iSpeed < 0) {
            motorSet(iPort, -(MC29[iSpeed]));
        }
        else {
            motorSet(iPort, 0);
        }
    }

    void left(int iSpeed) {
        trueSpeed(frontLeft.motorNum, iSpeed);
        trueSpeed(backLeft.motorNum, iSpeed);
    }

    void right(int iSpeed) {
        trueSpeed(frontRight.motorNum, iSpeed);
        trueSpeed(backRight.motorNum, iSpeed);
    }

    void speed(int iSpeed) {
        left(iSpeed);
        right(iSpeed);
    }
    void timed(int iSpeed, int duration) {
        speed(iSpeed);
        delay(duration);
        speed(0);
    } /*
    void waitUntil(int iSpeed, int target) {
        speed(iSpeed);
        if(sensor::get(enc) > target) {
            while(sensor::get(enc) > target) {
                delay(15);
            }
        }
        else if(sensor::get(enc) < taget) {
            while(sensor::get(enc) < target) {
                delay(15);
            }
        }
    }   */
    
    namespace teleop {
        void arcade(int speed, int turn) {
            left(speed + turn);
            right(speed + turn);
        }
    }
    }
