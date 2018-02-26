#ifndef ARM_H
#define ARM_H
#include "API.h"

namespace arm {
    typedef struct {
        int motorNum;
        int isReverse;
        bool isTruespeed;
    } motors;

    void init(int motorNum, int isReverse, char Location[]);
    void speed(int iSpeed);
    void timed(int iSpeed, int duration);
    void waitUntil(int iSpeed, int target);

    void teleop();
}


#endif