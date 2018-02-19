#include "../include/rollers.hpp"
#include "../include/joystick.hpp"

namespace rollers {
    motors main;

    void init(int motorNum, bool isReverse) {
        main.motorNum = motorNum;
        main.isReverse = isReverse;
    }

    void speed(int iSpeed) {
        motorSet(main.motorNum, iSpeed);
    } 
    void timed(int iSpeed, int duration) {
        speed(iSpeed);
        delay(duration);
        speed(0);
    } 

    int iOutput;
    void teleop() {
        if(joystick::digital(7, joystick::Left)) iOutput = 127;
        else if(joystick::digital(6,joystick::Down)) iOutput = -127;
        else iOutput = 15;
        speed(iOutput);
    }
}