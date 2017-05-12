#include "lcdRuling.h"

void pageChecker() {
  if (lcdReadButtons(uart1) == 1) {
    int PgNum = PgNum + 1;
  }
  if (lcdReadButtons(uart1) == 4) {
    int PgNum = PgNum - 1;
  }
}
