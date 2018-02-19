#ifndef DRIVE_H
#define DRIVE_H
#include "../include/API.h"

namespace drive {
    typedef struct {
        int motorNum;
        bool isReverse;
        bool isTruespeed;
    } motors;

    void init(int motorNum, bool isReverse, bool isTruespeed, char Location);
}

#endif
