#include "../include/mogo.hpp"
#include "../include/joystick.hpp"

namespace mogo {
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
        motorSet(right.motorNum, iSpeed);
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
        if(joystick::digital(7, joystick::Up)) iOutput = 127;
        else if(joystick::digital(6,joystick::Right)) iOutput = -127;
        else iOutput = 15;
        speed(iOutput);
    }
}