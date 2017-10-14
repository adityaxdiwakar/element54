#include "main.h"

void
autonomous() {
  if(analogRead(AUTO_POT) > 4000) {
    coneAutonLeft();
  }
  else if(analogRead(AUTO_POT) < 20) {
    mogoAutonBlue();
  }
  else if(analogRead(AUTO_POT) > 3000 && analogRead(AUTO_POT) < 4000) {
    startSequence();
  }
  else if(analogRead(AUTO_POT) < 3000 && analogRead(AUTO_POT) > 30) {
    mogoAutonRed();
  }
}
