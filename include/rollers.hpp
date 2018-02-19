#ifndef ROLLERS_H
#define ROLLERS_H
#include "API.h"

namespace rollers {
    typedef struct {
        int motorNum;
        bool isReverse;
        bool isTruespeed;
    } motors;

    void init(int motorNum, bool isReverse, bool isTruespeed, char Location[]);
    void speed(int iSpeed);
    void timed(int iSpeed, int duration);

    void teleop();
}


#endif