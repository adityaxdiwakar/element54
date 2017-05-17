#include "lcdRuling.h"

// PAGE NUMBERS and PAGE LISTS

void lcdGlobal() {
  if (Indexer == 0) {
    Indexer = 0;
    if (lcdReadButtons(uart1) == 4) {
      int PgNum = PgNum++;
    }
    if (lcdReadButtons(uart1) == 1) {
      int PgNum = PgNum--;
    }
  }
}

void lcdLocal() {
  if (Indexer == 1) {
    if (lcdReadButtons(uart1) == 4) {
      int PgNumLocal = PgNumLocal++;
    }
    if (lcdReadButtons(uart1) == 1) {
      int PgNumLocal = PgNumLocal--;
    }
  }
}
