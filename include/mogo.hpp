#ifndef MOGO_H
#define MOGO_H
#include "API.h"

namespace mogo {
    typedef struct {
        int motorNum;
        bool isReverse;
        bool isTruespeed;
    } motors;

    void init(int motorNum, bool isReverse, bool isTruespeed, char Location[]);
    void speed(int iSpeed);
    void timed(int iSpeed, int duration);
    void waitUntil(int iSpeed, int target);

    void teleop();
}


#endif