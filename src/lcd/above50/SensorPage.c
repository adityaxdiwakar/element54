#include "lcdRuling.h"

void Pg_Sensor() {
  lcdSetText(uart1, 1, "Sensors?");
  lcdSetText(uart1, 2, "<      >");

  if (lcdReadButtons(uart1) == 2) {
    int PgNum = PgNum * 10;
    pageChecker();
    }
  }
