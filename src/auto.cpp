#include "../include/main.h"

namespace autonFunc {
  typedef struct {
    int value;
    bool reset;
    bool turn;
    bool complete = false;
  } autonVal;

  autonVal drive, mogo, bar, lift;

  void driveCreateVoid(void*parameter) {
    drive.complete = false;
    if(drive.turn) {
      drive::auton::gyTurn(drive.value, drive.reset);
    }
    else {
      if(drive.value > 0) drive::waitUntil(127, drive.value, drive.reset);
      else if(drive.value < 0) drive::waitUntil(-127, drive.value, drive.reset);
    }
    drive.complete = true;
  }

void liftCreateVoid(void*parameter) {
  lift.complete = false;
  if(lift.value > sensors::arm::get()) arm::waitUntil(127, lift.value);
  else if(lift.value < sensors::arm::get()) arm::waitUntil(-127, lift.value);
  lift.complete = true;
}

void barCreateVoid(void*parameter) {
  bar.complete = false;
  if(bar.value > sensors::bar::get()) bar::waitUntil(127, bar.value);
  else if(bar.value < sensors::bar::get()) bar::waitUntil(-127, bar.value);
  bar.complete = true;
}

void mogoCreateVoid(void*parameter) {
  mogo.complete = false;
  if(mogo.value > sensors::mogo::get()) mogo::waitUntil(127, mogo.value);
  else if(mogo.value < sensors::mogo::get()) mogo::waitUntil(-127, mogo.value);
  mogo.complete = true;
}
}


const unsigned int stack = TASK_DEFAULT_STACK_SIZE;
const unsigned int prio = TASK_PRIORITY_DEFAULT;
TaskHandle barTask, liftTask, mogoTask, driveTask;

namespace mogo {
  bool blocked = false;
  void get(int coneAmount) {
    arm::speed(127);
    while(sensors::arm::get() < 1500) { delay(15); }
    mogo::speed(127);
    drive::speed(127);
    bar::speed(-127);
    while(sensors::arm::get() < 1750 || sensors::drive::right::get() < 1200 || sensors::mogo::get() < 3000) {
      delay(15);
      if(sensors::arm::get() > 1750) { 
        arm::speed(0);
      }
      if(sensors::mogo::get() > 3000) {
        mogo::speed(0);
        bar::speed(0);
      }
      if(sensors::drive::right::get() > 1200) {
        drive::speed(0);
      }
    }
    mogo::speed(0); arm::speed(0); drive::speed(0); bar::speed(0);
    mogo::speed(-127);
    arm::speed(-127);
    while(sensors::mogo::get() > 3000) {
      delay(15);
      if(sensors::arm::get() < 1575) {
        arm::speed(127);
        wait(50);
        arm::speed(0);
      }
    }
    arm::speed(-127); 
    while(sensors::arm::get() > 1500) { 
      delay(15);
    }
    arm::speed(0);
    mogo::speed(0);
    drive::auton::pid()
  }

  void put(char direction[]) {
  }
}




void autonomous() {
  mogo20::get(1);
} 