#include "main.h"

int counter = 0;
void lcdCounter()
{
    while(true) {
        lcdPrint(uart1, 1, "%d", counter);
        if(lcdReadButtons(uart1) == 4) counter -= 1;
        if(lcdReadButtons(uart1) == 1) counter += 1;
        if(lcdReadButtons(uart1) == 2) counter = 0;
    }
}