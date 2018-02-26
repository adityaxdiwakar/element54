#include "../include/main.h"

namespace rollers {
    motors main;

    void init(int motorNum, int isReverse) {
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

    int iOutput, rollTime, bSpin;
    void teleop() {
        if(joystick::digital(7, joystick::Left)) {
            iOutput = 127; 
            bSpin = false;
            }
        else if(joystick::digital(7,joystick::Down)) {
            iOutput = -127; 
            bSpin = true;
            rollTime = millis();
            }
        else if((millis()-rollTime < 1000) && bSpin) iOutput = -127;
        else if (sensors::arm::get() < 1800 && sensors::bar::get() < 900)
            iOutput = 127;
        else
          iOutput = 18;
        speed(iOutput);
    }
}