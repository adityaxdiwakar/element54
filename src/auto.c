#include "main.h"

void
autonomous() {
  if(analogRead(AUTO_POT) > 4000) {
    coneAutonLeft();
  }
  else if(analogRead(AUTO_POT) < 2048) {
    mogoAutonBlue();
  }
  else if(analogRead(AUTO_POT) < 4000 && analogRead(AUTO_POT) > 2048) {
    mogoAutonRed();
  }
}
