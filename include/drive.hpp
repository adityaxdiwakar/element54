#ifndef DRIVE_H
#define DRIVE_H
#include "API.h"

namespace drive {
    typedef struct {
        int motorNum;
        bool isReverse;
        int isTruespeed;
    } motors;

    void init(int motorNum, bool isReverse, bool isTruespeed, char Location[]);
    void trueSpeed(int iPort, int iSpeed);
    void left(int iSpeed);
    void right(int iSpeed);
    void speed(int iSpeed);
    void timed(int iSpeed, int duration);
    void waitUntil(int iSpeed, int target);

    namespace teleop {
        void arcade(int speed, int turn);
    }
}

#endif
