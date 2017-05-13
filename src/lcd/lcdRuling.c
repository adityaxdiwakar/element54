#include "lcdRuling.h"

// PAGE NUMBERS and PAGE LISTS

void lcdGlobal() {
  if (lcdReadButtons(uart1) == 4) {
    int PgNum = PgNum++;
  }
  if(lcdReadButtons(uart1) == 1) {
    int PgNum = PgNum--;
  }
}
