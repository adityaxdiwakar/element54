#include "lcdRuling.h"

void Pg_Sensor() {
  lcdSetText(uart1, 1, "Sensors?");
  lcdSetText(uart1, 2, "<      >");

  if (lcdReadButtons(uart1) == 2) {
    int PgNum = PgNum * 10;
    pageChecker();
  }
  if (PgNum == PgNum * 10) { //Gyro page
    lcdSetText(uart1, 1, "Gyro is");
    lcdPrint(uart1, 2, "%d", gyro);
  }
  if (PgNum == PgNum * 10 + 1) { //Autonomous potentiometer page
    lcdSetText(uart1, 1, "Auton Selector");
    lcdPrint(uart1, 2, "%d", autopot);
  }
}
