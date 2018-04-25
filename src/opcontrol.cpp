#include "../include/main.h"

void opCtrl() {
  drive::teleop::arcade(joystick::analog(2), joystick::analog(1));
  arm::teleop();
  mogo::teleop();
  rollers::teleop();
  bar::teleop();
  /*printf("arm %d mogo %d drive %d bar %d gyro %d fwd %d hor %d\n", sensors::arm::get(), sensors::mogo::get(), sensors::drive::get(), sensors::bar::get(), sensors::gyro::get()
                                                                 , joystick::analog(2), joystick::analog(1));*/
  lcdPrint(uart1, 1, "A: %d, M: %d", sensors::arm::get(), sensors::mogo::get());
  lcdPrint(uart1, 2, "B: %d", sensors::bar::get());
  delay(20);
  if(joystick::digital(8, joystick::Right)) autonomous();
}

using namespace std;
void operatorControl() {
  lcdSetBacklight(uart1, true);
  while(true) { 
    opCtrl();
    }
}

 
/*
 printf("Let's get started!\n");
  
  printf("Analog section first:\n");
  printf("When you are ready to proceed, press the button.");
  while(true) {
    if(analogRead(12) == LOW) break;
  }
  int pg = 0;
  while(true) {
    printf("Port %d @ %d\n", pg, analogRead(pg));
    if(digitalRead(12) == LOW) {
      pg++;
      wait(150);
    }
    if(pg > 8) break;
  }
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  printf("Digital section now:\n");
  printf("When you are ready to proceed, press the button.");
  while(true) {
    if(analogRead(12) == LOW) break;
  }
  pg = 0;
  while(true) {
    printf("Port %d @ %d\n", pg, digitalRead(pg));
    if(digitalRead(12) == LOW) {
      pg++;
      wait(150);
    }
    if(pg > 12) break;
  }

  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  printf("Motor section now:\n");
  printf("When you are ready to proceed, press the button.");
  while(true) {
    if(analogRead(12) == LOW) break;
  }
  pg = 0;
  int motorTest = 1;
  int dir = 127;
  while(true) {
    printf("Port %d @ %d\n", motorTest, dir);
    motorSet(motorTest, dir);
    if(digitalRead(12) == LOW) {
      dir = -dir;
      pg++;
      if(pg % 2 == 0) {
        motorTest++;
      }
      wait(150);
    }
    if(motorTest > 10) break;
  }
  */