#include "lcdRuling.h"

void Pg_Auto() {
  lcdSetText(uart1, 1, "Auto Selector");
  lcdSetText(uart1, 2, "<   Click.  >");
  if(lcdReadButtons(uart1) == 2) {
    int Indexer = 1;
  }
  }
