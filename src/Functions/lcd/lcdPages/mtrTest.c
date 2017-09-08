#include "lcd.h"
#include "MotorDef.h"
#include "arm.h"

void mtrTestPg() {
  //click the middle page
  lcdSetText(uart1, 1, "Motor Resp. Test");
  lcdSetText(uart1, 2, "[BACK]     NEXT>");
  if (lcdReadButtons(uart1) == 2) {
    localizer = true;
    //sets the localizer to true,
    //running this will cause a significant
    //delay in the program and no functions
    //will be able to operate for a short period of time
  }
}

void mtrConfigKernel() {
  //clicking the middle button will trigger this task, immediately
  lcdSetText(uart1, 1, "Testing...");
  lcdSetText(uart1, 2, "Kernel Test Start");
  for (mtrTest = 0; mtrTest < 11; mtrTest++) {
    motorSet(mtrTest, 6);
    int mtrLcl = motorGet(mtrTest);
    if (mtrLcl > 1) {
      lcdPrint(uart1, 2, "Motor %d passed.", mtrTest);
      delay(400);
    }
    if (mtrLcl < 1) {
      lcdPrint(uart1, 2, "Motor %d failed.", mtrTest);
      delay(750);
      lcdPrint(uart1, 2, "Kernel failed.");
      if (lcdReadButtons(uart1) == 2) {
        localizer = false;
      }
    }
  }
  if (mtrTest > 9) {
    lcdSetText(uart1, 2, "Kernel passed.");
    wait(1000);
    mtrPass_phase1 = true;
    PgNumLcl == 2;
  }
}

void mtrConfigPhys() {
  //passing the first test will result in this being completed.
  lcdSetText(uart1, 1, "Testing...");
  lcdSetText(uart1, 2, "Robot should be");
  delay(350);
  lcdSetText(uart1, 2, "in a safe env.");
  delay(350);
  lcdSetText(uart1, 2, "?  [Continue]  ?");
  if (lcdReadButtons(uart1) == 2) {
    lcdSetText(uart1, 2, "Starting...");
    //starting the arm test
    int apChangeConst = digitalRead(ArmPot);
    int apChange;
    int apBreak = false;
    while (apChange > apChangeConst + 500 && apBreak == false) {
      apChange = digitalRead(ArmPot);
      SetArm(127);
      lcdPrint(uart1, 2, "Arm @ %d", apChange);
      int lolzer = false;
      if ((motorGet(5) > 30) || (motorGet(6) > 30) && (digitalRead(ArmPot) > apChangeConst) && (lolzer > 10)) {
        //initiating mega-super-safe, safe like a condom fail safe to prevent failure ...
        localizer = false;
        SetArm(0);
        lcdSetText(uart1, 2, "lol it gon break");
        wait(500);
        apBreak = true;
      }
      lolzer++;
    }
    SetArm(0);
    if (apBreak) {
      lcdSetText(uart1, 2, "Arm Failed!");
      delay(500);
      lcdSetText(uart1, 2, "[Cont]    [Quit]");
      bool noClick = true;
      bool quitClick = false;
      bool contClick = false;
      while (noClick) {
        if (lcdReadButtons(uart1) == 4) {
          noClick = false;
          contClick = true;
        }
        if (lcdReadButtons(uart1) == 1) {
          noClick = false;
          quitClick = true;
        }
      }
      if (quitClick) {
        localizer = false;
        if (contClick) {
          lcdSetText(uart1, 2, "Test successful.");
          delay(500);
          lcdSetText(uart1, 2, "Un-mounting.");
          localizer = false;
        }
      }
    }
  }
}
