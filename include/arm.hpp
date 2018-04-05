#ifndef ARM_H
#define ARM_H
#include "API.h"

namespace arm {
    typedef struct {
        int motorNum;
        bool isReverse;
        int isTruespeed;
    } motors;

    void init(int motorNum, bool isReverse, char Location[]);
    void speed(int iSpeed);
    void timed(int iSpeed, int duration);
    void waitUntil(int iSpeed, int target);

    void teleop();
}


#endif