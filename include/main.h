#ifndef MAIN_H_
#define MAIN_H_

#include "API.h"
#include "joystick.hpp"
#include "arm.hpp"
#include "drive.hpp"
#include "mogo.hpp"
#include "sensors.hpp"
#include "bar.hpp"
#include "rollers.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void autonomous();
void initializeIO();
void initialize();
void operatorControl();

#ifdef __cplusplus
}
#endif

#endif
