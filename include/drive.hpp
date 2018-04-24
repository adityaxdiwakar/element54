#ifndef DRIVE_H
#define DRIVE_H
#include "API.h"

namespace drive {
    typedef struct {
        int motorNum;
        bool isReverse;
        int isTruespeed;
    } motors;

    typedef struct {
        float current;
        float kP;
        float kI;
        float kD;
        float target;
        float integral;
        float error;
        float derivative;
        float lastError;
    } pid;

    void init(int motorNum, bool isReverse, bool isTruespeed, char Location[]);
    void trueSpeed(int iPort, int iSpeed);
    void left(int iSpeed);
    void right(int iSpeed);
    void vDrive(void*parameter);
    void vRotate(void*parameter);
    void gyTurn(void*parameter);
    void autoDrive(void*parameter);
    void speed(int iSpeed);
    void timed(int iSpeed, int duration);
    void waitUntil(int iSpeed, int target);

    namespace teleop {
        void arcade(int speed, int turn);
    }
}

#endif
