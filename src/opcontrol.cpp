#include "../include/main.h"
#include "../include/drive.hpp"
#include "../include/joystick.hpp"
  


void opCtrl() {
  drive::teleop::arcade(joystick::analog(1), joystick::analog(2));
} 

void operatorControl() {
  while (isEnabled()) {
    delay(50);
  }
}
