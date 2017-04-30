#include "API.h"
#include "lcdRuling.h"

void WelcomePg () {
  setLcdText(uart1, 1, " Welcome Master ");
  setLCDText(uart1, 1, "<              >");
};
