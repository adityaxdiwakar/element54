#include "../include/main.h"

namespace bar {
    motors left;
    motors right;

    void init(int motorNum, bool isReverse, char location[]) {
        if(location == "left") {
            left.motorNum = motorNum;
            left.isReverse = isReverse;
        } else if(location == "right") {
            right.motorNum = motorNum;
            right.isReverse = isReverse;
        }
    }

    void speed(int iSpeed) {
        motorSet(left.motorNum, iSpeed);
        motorSet(right.motorNum, -iSpeed);
    } 
    void timed(int iSpeed, int duration) {
        speed(iSpeed);
        delay(duration);
        speed(0);
    } /*
    void waitUntil(int iSpeed, int target) {
        speed(iSpeed);
        if(sensors::get(arm) > target) {
            while(sensors::get(arm) > target) {
                delay(15);
            }
        }
        if(sensors::get(arm) < target) {
            while(sensors::get(arm) < target) {
                delay(15);
            }
        }   
    } */

    int iOutput;
    void teleop() {
        if(joystick::digital(5, joystick::Up) && sensors::bar::get() < 3100) iOutput = (3100 - sensors::bar::get()) / 18;
        else if(joystick::digital(5, joystick::Up)) iOutput = 127;
        else if(joystick::digital(5, joystick::Down)) iOutput = -127;
        else iOutput = 0;
        
        if(iOutput > 127) iOutput = 127;
        speed(iOutput);
    }
}
