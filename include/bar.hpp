#ifndef BAR_H
#define BAR_H
#include "API.h"

namespace bar {
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