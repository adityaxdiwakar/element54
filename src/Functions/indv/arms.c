#include "arm.h"
#include "API.h"
#include "MotorDef.h"

void posSetArm(int posY) {
  int pos1 = analogRead(ArmPot);
  SetArm(127);
  int pos;
  if(analogRead(ArmPot) > posY) {
    for (pos = pos1; pos < posY; pos++) {
      /* code */
    }
  }
  }
