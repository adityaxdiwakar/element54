#include "../include/main.h"

namespace mogo {
    motors left;
    motors right;

    void init(int motorNum, int isReverse, char location[]) {
        if(location == "left") {
            left.motorNum = motorNum;
            left.isReverse = isReverse;
        } else if(location == "right") {
            right.motorNum = motorNum;
            right.isReverse = isReverse;
        }
    }

    void speed(int iSpeed) {
        motorSet(left.motorNum, iSpeed * left.isReverse);
        motorSet(right.motorNum, iSpeed * right.isReverse);
    } 
    void timed(int iSpeed, int duration) {
        speed(iSpeed);
        delay(duration);
        speed(0);
    } 
    //127 for down
    void waitUntil(int iSpeed, int target) {
        speed(iSpeed);
        if(sensors::mogo::get() > target) {
            while(sensors::mogo::get() > target) {
                delay(15);
            }
        }
        if(sensors::mogo::get() < target) {
            while(sensors::mogo::get() < target) {
                delay(15);
            }
        }   
        speed(0);
    } 

    int iOutput;
    void teleop() {
        if(joystick::digital(7, joystick::Up)) iOutput = 127;
        else if(joystick::digital(7,joystick::Right)) iOutput = -127;
        else if(sensors::mogo::get() > 3000) iOutput = 30;
        else iOutput = 0;
        speed(iOutput);
    }
}