#include "API.h"
#include "lcdRuling.h"

void VariableViewer () {
  lcdSetText(uart1, 1, " View Variables ");
  lcdSetText(uart1, 2, "Home           >");
  if(LCDReadButtons(uart1) == 2) {
    PgNum = PgNum * 10;
    int PrevPgNum = PgNum; };

  if(PgNum = PrevPgNum + 1) {
    lcdSetText(uart1, 1, "    Sensor 1    ")
    lcdPrint(uart1, 2, "<     %d     >", PgNumLocal/*Sensor Val */);

  }
};
