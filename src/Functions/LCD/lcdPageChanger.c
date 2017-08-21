#include "API.h"
#include "lcdRuling.h"

void lcdChange() {
//If the left button is pressed, decrease the page number by 1.
if(lcdReadButtons(uart1) == 4) {
  PgNum = PgNum - 1;
};

//If the right button is pressed, increase the page number by 1.
if(lcdReadButtons(uart1) == 1) {
  PgNum = PgNum + 1;
};
};

//Do nothing if the middle button is pressed, will be used in individual pages.
