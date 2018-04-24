#include "../include/mogo.hpp"
#include "../include/joystick.hpp"
#include "../include/sensors.hpp"

namespace mogo {
    motors main;

    void init(int motorNum, bool isReverse, char location[]) {
        if(location == "main") {
            main.motorNum = motorNum;
            main.isReverse = isReverse;
        }
    }

    void speed(int iSpeed) {
        if(main.isReverse) {
            motorSet(main.motorNum, iSpeed * main.isReverse);
        }
    } 

    void timed(int iSpeed, int duration) {
        speed(iSpeed);
        delay(duration);
        speed(0);
    } 
    
    /*
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
        else if(joystick::digital(7,joystick::Right)) iOutput = -127;
        else if(sensors::mogo::get() > 3600) iOutput = 30; 
        else if(sensors::mogo::get() < 1300) iOutput = -20;
        else iOutput = 0;
        speed(iOutput);
    }
}