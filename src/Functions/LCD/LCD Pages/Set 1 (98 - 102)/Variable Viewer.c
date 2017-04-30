#include "API.h"
#include "lcdRuling.h"

void VariableViewer () {
  lcdSetText(uart1, 1, " View Variables ");
  lcdSetNext(uart1, 2, "<              >");
  if(LCDReadButtons(uart1) == 2) {
    PageNumber = PageNumber * 10;
    int PrevPageNumber = PageNumber; };

  if(PageNumber = PrevPageNumber + 1) {
    lcdSetText(uart1, 1, "    Sensor 1    ")
    lcdPrint(uart1, 2, "<     %d     >", PageNumber/*Sensor Val */);

  }
};
