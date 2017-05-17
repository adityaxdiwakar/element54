#include "lcdRuling.h"

void PageDir() {
if (PgNum == 50) {
  Pg_Home();
} 
if (PgNum == 49) {
  Pg_Auto();
}
if (PgNum == 51) {
  Pg_Sensor();
} /*
if (PageNum == 48) {
}
if (PageNum == 52) {
}
if (PageNum == 47) {
}
*/
}
