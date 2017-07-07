#include "API.h"
#include "JumperDef.h"
#include "MotorDef.h"
#include "PreferredPronouns.h"
#include "arm.h"
#include "intake.h"
#include "misc.h"
#include "recording.h"
char filename_buf[4];
char *GenFileName(unsigned short *duration) {
  if (digitalRead(Jumper_SkillsOrAuton)) {
    *filename_buf = 'A'; // Autonomous
    *duration = 15000;   // 15 Seconds
    filename_buf[1] = digitalRead(Jumper_RedOrBlue_And_LeftOrRight)
                          ? 'R'
                          : 'L'; // L: Left, R: Right
  } else {
    *filename_buf = 'S'; // Skills
    *duration = 60000;   // 60 Seconds
    filename_buf[1] = digitalRead(Jumper_RedOrBlue_And_LeftOrRight)
                          ? 'B'
                          : 'R'; // R: Red, B: Blue
  };
  filename_buf[2] = '0' + ((digitalRead(Jumper_version1or0) ? 0 : 1) |
                           (digitalRead(Jumper_version2or0) ? 0 : 2));
  filename_buf[3] = '\0';
  return filename_buf;
};
void ErrorBlinkInfinite() {
  char blink = 0;
  while (1) {
    digitalWrite(StatusLED, blink);
    blink = !blink;
    wait(100);
  };
};
void ErrorMultiBlinkInf(unsigned char nblinks) {
  while (1) {
    for (unsigned char i = 0; i < nblinks; i++) {
      digitalWrite(StatusLED, 0);
      wait(100);
      digitalWrite(StatusLED, 1);
      wait(100);
    };
    wait(500);
  };
};
void FollowInstructions() {
  unsigned short Duration;
  char *filename = GenFileName(&Duration);
  digitalWrite(StatusLED, 0);
  FILE *file = fopen(filename, "r");
  if (!file)
    ErrorBlinkInfinite(); // Could not open the file, presumably because it
                          // doesn't exist.
  fseek(file, 0, SEEK_END);
  unsigned int instructioncount; // = ftell(file) /
                                 // (membersize(Instruction,time) +
                                 // membersize(Instruction,label) +
                                 // membersize(Instruction,power));
  // fseek(file,0,SEEK_SET);
  if (fread(&instructioncount, sizeof(instructioncount), 1, file) <
      sizeof(instructioncount))
    goto CLOSE_ERRBLINK;
  Instruction *instructions = malloc(sizeof(Instruction) * instructioncount);
  if (!instructions)
    goto ALLOCFAILURE;
  unsigned int iter = instructioncount;
  Instruction *instrptr = instructions;
  while (iter--) {
    if (fread(&(instrptr->time), sizeof(instrptr->time), 1, file) <
        sizeof(instrptr->time))
      goto DEALLOC_CLOSE_ERRBLINK;
    if (fread(&(instrptr->label), sizeof(instrptr->label), 1, file) <
        sizeof(instrptr->label))
      goto DEALLOC_CLOSE_ERRBLINK;
    if (fread(&(instrptr->power), sizeof(instrptr->power), 1, file) <
        sizeof(instrptr->power))
      goto DEALLOC_CLOSE_ERRBLINK;
    instrptr++;
  };
  fclose(file); // We're done with this.
  digitalWrite(StatusLED, 1);
  unsigned int StartTime = millis();
  instrptr = instructions;
  while (instructioncount--) // Don't try to read past the end of the file.
  {
    // Busy-wait until it's time to apply the instruction.
    while (millis() < StartTime + instrptr->time)
      ; // wait(20);

    signed char power = instrptr->power;
    switch (instrptr->label) // Change what this instruction specifies.
    {
    case Label_BaseLEFT:
      motorSet(Base_FL, power);
      motorSet(Base_FR, power);
      motorSet(Base_BL, power);
      break;
    case Label_BaseRIGHT:
      motorSet(Base_FR, power);
      motorSet(Base_FR2, power);
      motorSet(Base_BR, power);
      break;
    case Label_Arm:
      SetArm(power);
      break;
    case Label_IntakeA:
      SetIntakeA(power);
      break;
    case Label_IntakeB:
      SetIntakeB(power);
    };
    instrptr++;
  };
  // while (millis() < Duration + StartTime);
  RobotOff();
  return;

DEALLOC_CLOSE_ERRBLINK:
  free(instructions);
CLOSE_ERRBLINK:
  fclose(file);
  ErrorMultiBlinkInf(2);

ALLOCFAILURE:
  free(instructions);
  ErrorMultiBlinkInf(3);
};
