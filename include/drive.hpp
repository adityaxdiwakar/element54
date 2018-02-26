#ifndef DRIVE_H
#define DRIVE_H
#include "API.h"

namespace drive {
    typedef struct {
        int motorNum;
        int isReverse;
        bool isTruespeed;
    } motors;

    void init(int motorNum, int isReverse, bool isTruespeed, char Location[]);
    void trueSpeed(int iPort, int iSpeed);
    void left(int iSpeed);
    void right(int iSpeed);
    void speed(int iSpeed);
    void timed(int iSpeed, int duration);
    void waitUntil(int iSpeed, int target, bool reset);

    namespace auton {
        void pid(int distance);
        void gyTurn(int heading, bool reset);
    }
    namespace teleop {
        void arcade(int speed, int turn);
    }
}

#endif
