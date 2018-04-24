#include "../include/rollers.hpp"
#include "../include/joystick.hpp"
#include "../include/sensors.hpp"

namespace rollers {
    motors main;

    void init(int motorNum, bool isReverse) {
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

    int iOutput; int startTime; bool toggled;
    void teleop() {
        if(joystick::digital(7, joystick::Left)) {
            iOutput = 127;
            toggled = false;
        }
        else if(joystick::digital(7,joystick::Down)) {
            iOutput = -127;
            toggled = true;
            startTime = millis();
        }
        else if(sensors::arm::get() < 1250 && sensors::bar::get() < 1600) iOutput = 60;
        else iOutput = 15;

        if(toggled && (millis() - startTime < 500)) iOutput = -127;
        speed(iOutput);
    }
}