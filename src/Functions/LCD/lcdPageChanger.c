#include "API.h"
#include "lcdRuling.h"

//If the left button is pressed, decrease the page number by 1.
if(lcdReadButtons(uart1) == 4) {
  PageNumber = PageNumber - 1;
};

//If the right button is pressed, increase the page number by 1.
if(lcdReadButtons(uart1) == 1) {
  PageNumber = PageNumber + 1;
};

//Do nothing if the middle button is pressed, will be used in individual pages.
