#include "main.h"

void findMotors() {
int i = 1;
    while (i <= 10)
    {
      while (true)
      {
        lcdPrint(uart1, 1, "   Motor %d    ", i);
        lcdSetText(uart1, 2, "[+]    [N]   [-]");
        if (lcdReadButtons(uart1) == 1)
        {
          motorSet(i, 127);
        }
        else if (lcdReadButtons(uart1) == 4)
        {
          motorSet(i, -127);
        }
        else
        {
          motorSet(i, 0);
        }
        if (lcdReadButtons(uart1) == 2)
        {
          break;
        }

        delay(20);
      }
      i++;
      delay(250);
    }
}