#include "../include/main.h"

namespace bar {
    motors main;

    void init(int motorNum, int isReverse, char location[]) {
        main.motorNum = motorNum;
        main.isReverse = isReverse;
    }

    void speed(int iSpeed) {
        motorSet(main.motorNum, iSpeed * main.isReverse);
    } 
    void timed(int iSpeed, int duration) {
        speed(iSpeed);
        delay(duration);
        speed(0);
    } 
    void waitUntil(int iSpeed, int target) {
        speed(iSpeed);
        if(sensors::bar::get() > target) {
            while(sensors::bar::get() > target) {
                delay(15);
            }
        }
        if(sensors::bar::get() < target) {
            while(sensors::bar::get() < target) {
                delay(15);
            }
        }
        speed(0);   
    } 

    int iOutput;
    void teleop() {
        if(joystick::digital(5, joystick::Up)) iOutput = 127;
        else if(joystick::digital(5,joystick::Down)) iOutput = -127;
        else if (sensors::bar::get() > 1500)
            iOutput = 15;
        else
            iOutput = -15;

        speed(iOutput);
    }
}