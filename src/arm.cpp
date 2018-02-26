#include "../include/main.h"


namespace arm {
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
    void waitUntil(int iSpeed, int target) {
        speed(iSpeed);
        if(sensors::arm::get() > target) {
            while(sensors::arm::get() > target) {
                delay(15);
            }
        }
        if(sensors::arm::get() < target) {
            while(sensors::arm::get() < target) {
                delay(15);
            }
        }   
        speed(0);
    } 

    int iOutput;
    void teleop() {
        if(joystick::digital(6, joystick::Up)) iOutput = 127;
        else if(joystick::digital(6,joystick::Down)) iOutput = -127;
        else if (sensors::arm::get() < 1500)
            iOutput = -20;
        else
            iOutput = 15;
        speed(iOutput);
    }
}