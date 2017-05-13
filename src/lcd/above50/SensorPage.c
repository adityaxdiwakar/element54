#include "lcdRuling.h"

void Pg_Sensor() {
  lcdPrint(uart1, 1, "G: %d AP: %d", gyro, autopot);
  lcdSetText(uart1, 2, "<       >");
}
