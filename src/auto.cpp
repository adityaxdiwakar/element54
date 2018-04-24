#include "../include/main.h"


void mogoAutonMaster(int iCone) {
  int initSensors = sensors::gyro::get();
  sensors::drive::reset();
  sensors::gyro::reset();
  drive::speed(127);
  arm::speed(127);
  while(sensors::arm::get() < 800) 
    delay(15);
  mogo::speed(127);
  drive::speed(127);
  while(sensors::mogo::get() < 3850 || sensors::drive::get() < 500) {
    if(sensors::arm::get() > 1000) 
      arm::speed(10);
    if(sensors::mogo::get() > 3850) 
      mogo::speed(25);
    if(sensors::drive::get() > 500)
      drive::speed(0);
    delay(15);
  }
  mogo::speed(127);
  while(sensors::mogo::get() < 3900) 
    delay(15);
  mogo::speed(25);
  drive::speed(127);
  while(sensors::drive::get() < 1200) 
    delay(15);
  drive::speed(0);
  bar::speed(20);
  mogo::speed(-127);
  while(sensors::mogo::get() > 1600)  {
    delay(15); 
  }
  mogo::speed(0);
  arm::speed(-127);
  wait(150);
  rollers::speed(-127);
  wait(50);
  arm::speed(127);
  wait(200);
  arm::speed(15);
  rollers::speed(0);
  wait(100);


  bar::speed(-127);
  drive::speed(63);
  int dCurrent = sensors::drive::get();
  while(sensors::bar::get() > 1050 || sensors::drive::get() - dCurrent < 75) {
    if(sensors::bar::get() < 2200 && sensors::arm::get() > 730) arm::speed(-127);
    if(sensors::arm::get() < 730) arm::speed(0);
    if(sensors::bar::get() < 1050) bar::speed(0);
    if(sensors::drive::get() - dCurrent > 75) drive::speed(0);
    delay(15);
  }
  drive::speed(0);
  bar::speed(-15);
  arm::speed(-127);
  rollers::speed(127);
  while(sensors::arm::get() > 730) {
    delay(15);
  }
  arm::speed(-15);
  wait(100);
  arm::speed(127);
  rollers::speed(40);
  while(sensors::arm::get() > 2800) {
    delay(15);
    printf("%d\n", sensors::arm::get());
  }
  bar::speed(127);
  arm::speed(-127);   
  while(sensors::arm::get() > 730 || sensors::bar::get() < 3200) {
    if(sensors::arm::get() < 730) arm::speed(0);
    if(sensors::bar::get() > 3200) bar::speed(20);
    delay(15);
  }
  wait(50);
  rollers::speed(-127);
  wait(100);
  arm::speed(127);
  wait(150);
  arm::speed(0);


  bar::speed(-127);
  drive::speed(63);
  dCurrent = sensors::drive::get();
  while(sensors::bar::get() > 1050 || sensors::drive::get() - dCurrent < 100) {
    if(sensors::bar::get() < 2200 && sensors::arm::get() > 730) arm::speed(-127);
    if(sensors::arm::get() < 730) arm::speed(0);
    if(sensors::bar::get() < 1050) bar::speed(0);
    if(sensors::drive::get() - dCurrent > 100) drive::speed(0);
    delay(15);
  }
  drive::speed(63);
  wait(250);
  drive::speed(0);
  bar::speed(-15); 
  arm::speed(-127);
  rollers::speed(127);
  while(sensors::arm::get() > 730) {
    delay(15);
  }
  wait(50);
  arm::speed(-15);
  wait(250);  

  


  int dValue = -1850;
  sensors::drive::reset();
  TaskHandle driveTask = taskCreate(drive::vDrive, TASK_DEFAULT_STACK_SIZE, (void*)dValue, TASK_PRIORITY_DEFAULT);
  bar::speed(-127);
  while(sensors::bar::get() > 1050) { delay(15); }
  bar::speed(0);


  arm::speed(127);
  while(sensors::arm::get() > 2400) 
    delay(15);
  bar::speed(127);
  arm::speed(-127);   
  while(sensors::arm::get() < 2950 || sensors::bar::get() < 3200) {
    if(sensors::arm::get() > 2950) arm::speed(0);
    if(sensors::bar::get() > 3200) bar::speed(20);
    delay(15);
  }
  wait(50);
  rollers::speed(-127);
  wait(100);
  arm::speed(127);
  wait(250);  
  arm::speed(10);
  
  
  while(sensors::drive::get() > -1800) { delay(15); }
  delay(500);
  taskDelete(driveTask);
  drive::speed(0);

  int gyValue = 45;
  TaskHandle turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyValue, TASK_PRIORITY_DEFAULT);
  while(sensors::gyro::get() > 45) {delay(15);}
  delay(500);
  taskDelete(turnTask);

  dValue = 550;
  sensors::drive::reset();
  driveTask = taskCreate(drive::vDrive, TASK_DEFAULT_STACK_SIZE, (void*)dValue, TASK_PRIORITY_DEFAULT);
  while(sensors::drive::get() < 550) { delay(15); }
  delay(250);
  taskDelete(driveTask);
  drive::speed(0);

  gyValue = 135;
  turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyValue, TASK_PRIORITY_DEFAULT);
  while(sensors::gyro::get() > 135) {delay(15);}
  delay(500);
  taskDelete(turnTask);

  drive::speed(127);
  wait(1200);
  drive::speed(0);
  arm::speed(127); bar::speed(127); 
  mogo::speed(127);
  wait(250);
  arm::speed(10); bar::speed(10); 
  while(sensors::mogo::get() < 3850) {
    delay(15);
  }
  drive::speed(0); mogo::speed(0);
  wait(150);
  drive::speed(-127);
  wait(250);
  mogo::speed(-127);
  wait(350);
  arm::speed(-127);
  wait(250);
  drive::speed(0);
  arm::speed(0);
  mogo::speed(0);
}

void autonomous() {
  mogoAutonMaster(1);
}
