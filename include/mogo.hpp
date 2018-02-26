#ifndef MOGO_H
#define MOGO_H
#include "API.h"

namespace mogo {
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