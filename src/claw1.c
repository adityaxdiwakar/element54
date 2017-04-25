#include <MotorDef.h>
#include <API.h>
#include <claw.h>

void clawSet(int speed) {
  motorSet(ClawRightMotor, speed);
  motorSet(ClawLeftMotor, -speed);
}
