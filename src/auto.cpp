#include "../include/main.h"
#include "string.h"
#define H_back = -1850
#define M_back = -1850
#define L_back = -1500

unsigned long iStart;
void mogoPreloadMaster(int iCone) {
  iStart = millis();
  sensors::drive::reset();
  sensors::gyro::reset();
  rollers::speed(-40);
  drive::speed(127);
  if(sensors::arm::get() < 2250) {
    arm::speed(127);
    while(sensors::arm::get() < 2250) 
      delay(15);
  }
  mogo::speed(127);
  drive::speed(127);
  while(sensors::mogo::get() < 2850 || sensors::drive::get() < 500) {
    if(sensors::arm::get() < 2350) 
      arm::speed(10);
    if(sensors::mogo::get() > 2850) 
      mogo::speed(25);
    if(sensors::drive::get() > 500)
      drive::speed(0);
    delay(15);
  }
  mogo::speed(127);
  while(sensors::mogo::get() < 2850) 
    delay(15);
  mogo::speed(20);
  drive::speed(127);
  while(sensors::drive::get() < 1200)
    delay(15);
  drive::speed(0);
  bar::speed(20);
  mogo::speed(-127);
  while(sensors::mogo::get() > 800)  {
    delay(15); 
    }
  mogo::speed(-15);
  

  int dValue = -750;
  sensors::drive::reset();
  TaskHandle driveTask = taskCreate(drive::vDrive, TASK_DEFAULT_STACK_SIZE, (void*)dValue, TASK_PRIORITY_DEFAULT);


  arm::speed(-127);
  wait(150);
  rollers::speed(127);
  wait(50);
  arm::speed(127);
  wait(50);
  arm::speed(15);
  rollers::speed(0);
  wait(100); 
  arm::speed(127);
  while(sensors::arm::get() < 2730) {
    delay(15);
  }
  arm::speed(0);
  


  while(sensors::drive::get() > -750) {
     printf("%d\n", sensors::drive::get());
     delay(15);   
  }
  delay(250);
  taskDelete(driveTask);
  drive::speed(0);

  int rValue = -53;
  TaskHandle turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)rValue, TASK_PRIORITY_DEFAULT);

   
  bar::speed(-127);
  while(sensors::bar::get() < 2500) {
    delay(15);
  }
  bar::speed(0);

  while(sensors::gyro::get() > -53) {delay(15);}
  delay(500);
  taskDelete(turnTask); 
  drive::speed(0);

  //starting first preload
  int coneHeight = 2650;
  drive::speed(7);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 50) delay(15);
  rollers::speed(-40); 
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2250 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2250) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

 //second cone
  bar::speed(-127);
  wait(125);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::bar::get() < 2500) {
    if(sensors::bar::get() > 1350 && sensors::arm::get() > coneHeight) arm::speed(-127);  
    printf("%d\n", sensors::bar::get());
    if(sensors::arm::get() < coneHeight) arm::speed(0);
    delay(15); 
  }
  bar::speed(0);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 100) delay(15);
  rollers::speed(-40);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2325 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2325) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

  //third cone
  bar::speed(-127);
  wait(200);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::bar::get() < 2500) {
    if(sensors::bar::get() > 1350 && sensors::arm::get() > coneHeight) arm::speed(-127);  
    printf("%d\n", sensors::bar::get());
    if(sensors::arm::get() < coneHeight) arm::speed(0);
    delay(15); 
  }
  bar::speed(0);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 150) delay(15);
  rollers::speed(-40);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2425 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2425) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

  //fourth cone
  bar::speed(-127);
  wait(200);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::bar::get() < 2500) {
    if(sensors::bar::get() > 1350 && sensors::arm::get() > coneHeight) arm::speed(-127);  
    printf("%d\n", sensors::bar::get());
    if(sensors::arm::get() < coneHeight) arm::speed(0);
    delay(15); 
  }
  bar::speed(0);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 200) delay(15);
  rollers::speed(-40);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2525 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2525) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

  //fifth cone
  bar::speed(-127);
  wait(200);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::bar::get() < 2500) {
    if(sensors::bar::get() > 1350 && sensors::arm::get() > coneHeight) arm::speed(-127);  
    printf("%d\n", sensors::bar::get());
    if(sensors::arm::get() < coneHeight) arm::speed(0);
    delay(15); 
  }
  bar::speed(0);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 250) delay(15);
  rollers::speed(-40);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2625 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2625) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

  //sixth cone
  bar::speed(-127);
  wait(200);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::bar::get() < 2500) {
    if(sensors::bar::get() > 1350 && sensors::arm::get() > coneHeight) arm::speed(-127);  
    printf("%d\n", sensors::bar::get());
    if(sensors::arm::get() < coneHeight) arm::speed(0);
    delay(15); 
  }
  bar::speed(0);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 300) delay(15);
  rollers::speed(-40);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2725 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2725) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

  //seventh cone
  bar::speed(-127);
  wait(200);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::bar::get() < 2500) {
    if(sensors::bar::get() > 1350 && sensors::arm::get() > coneHeight) arm::speed(-127);  
    printf("%d\n", sensors::bar::get());
    if(sensors::arm::get() < coneHeight) arm::speed(0);
    delay(15); 
  }
  bar::speed(0);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 350) delay(15);
  rollers::speed(-40);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2825 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2825) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

  //eight cone
  bar::speed(-127);
  wait(200);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::bar::get() < 2500) {
    if(sensors::bar::get() > 1350 && sensors::arm::get() > coneHeight) arm::speed(-127);  
    printf("%d\n", sensors::bar::get());
    if(sensors::arm::get() < coneHeight) arm::speed(0);
    delay(15); 
  }
  bar::speed(0);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 425) delay(15);
  rollers::speed(-40);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2925 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2925) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

  //ninth cone
  bar::speed(-127);
  wait(200);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::bar::get() < 2500) {
    if(sensors::bar::get() > 1350 && sensors::arm::get() > coneHeight) arm::speed(-127);  
    printf("%d\n", sensors::bar::get());
    if(sensors::arm::get() < coneHeight) arm::speed(0);
    delay(15); 
  }
  bar::speed(0);
  arm::speed(-127);
  rollers::speed(-127);
  while(sensors::arm::get() > coneHeight) delay(15);
  arm::speed(127);
  while(sensors::arm::get() < coneHeight + 550) delay(15);
  rollers::speed(-40);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2950 || sensors::bar::get() > 1055) {
    if(sensors::arm::get() < 2950) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  rollers::speed(127);
  wait(100);
  arm::speed(127);
  wait(75);
  arm::speed(0);

  printf("%.2f", (millis() - iStart));
}

void mogoAutonMaster(int iCone, int distBack = -1850) {
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

  
  sensors::drive::reset();
  TaskHandle driveTask = taskCreate(drive::vDrive, TASK_DEFAULT_STACK_SIZE, (void*)distBack, TASK_PRIORITY_DEFAULT);
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
  
  
  while(sensors::drive::get() > distBack+50) { delay(15); }
  delay(500);
  taskDelete(driveTask);
  drive::speed(0);
}

void mogoSlaveFive(char direction[]) {
  int gyValue = strcmp(direction, "red") ? 180 : strcmp(direction, "blue") ? -180 : 180;
  TaskHandle turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyValue, TASK_PRIORITY_DEFAULT);
  while(abs(sensors::gyro::get()) < abs(gyValue)) {delay(15);}
  delay(500);
  taskDelete(turnTask);  

  rollers::speed(-127);
  arm::speed(127);
  wait(100);
  arm::speed(0);
  rollers::speed(0);
  mogo::speed(127);
  while(sensors::mogo::get() < 2500)
    delay(15);
  mogo::speed(63);
  while(sensors::mogo::get() < 3900) 
    delay(15);
  mogo::speed(20);
  drive::speed(-127);
  wait(500);
  drive::speed(0);
}

void mogoSlaveTen(char direction[]) {
  int gyValue = strcmp(direction, "red") ? 45 : strcmp(direction, "blue") ? -45 : 45;
  TaskHandle turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyValue, TASK_PRIORITY_DEFAULT);
  while(abs(sensors::gyro::get()) < abs(gyValue)) {delay(15);}
  delay(500);
  taskDelete(turnTask);  

  int dValue = 200;
  sensors::drive::reset();
  TaskHandle driveTask = taskCreate(drive::vDrive, TASK_DEFAULT_STACK_SIZE, (void*)dValue, TASK_PRIORITY_DEFAULT);
  while(sensors::drive::get() < 550) { delay(15); }
  delay(250);
  taskDelete(driveTask);
  drive::speed(0);

  gyValue = (strcmp(direction, "red") == 0) ? 135 : (strcmp(direction, "blue") == 0) ? -135 : 135;
  turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyValue, TASK_PRIORITY_DEFAULT);
  while(abs(sensors::gyro::get()) < abs(gyValue)) {delay(15);}
  delay(500);
  taskDelete(turnTask);

  drive::speed(30);
  wait(300);
  while(sensors::mogo::get() < 2500)
    delay(15);
  drive::speed(0);
  mogo::speed(63);
  while(sensors::mogo::get() < 3900) 
    delay(15);
  mogo::speed(20);
  drive::speed(-127);
  wait(500);
  drive::speed(0);
}

void mogoSlaveTwenty(char direction[]) {
  int gyValue = strcmp(direction, "red") ? 45 : strcmp(direction, "blue") ? -45 : 45;
  TaskHandle turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyValue, TASK_PRIORITY_DEFAULT);
  while(abs(sensors::gyro::get()) < abs(gyValue)) {delay(15);}
  delay(500);
  taskDelete(turnTask);

  int dValue = 550;
  sensors::drive::reset();
  TaskHandle driveTask = taskCreate(drive::vDrive, TASK_DEFAULT_STACK_SIZE, (void*)dValue, TASK_PRIORITY_DEFAULT);
  while(sensors::drive::get() < 550) { delay(15); }
  delay(250);
  taskDelete(driveTask);
  drive::speed(0);

  gyValue = (strcmp(direction, "red") == 0) ? 135 : (strcmp(direction, "blue") == 0) ? -135 : 135;
  turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyValue, TASK_PRIORITY_DEFAULT);
  while(abs(sensors::gyro::get()) < abs(gyValue)) {delay(15);}
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

void stationaryMaster(int iCone, char direction[]) {
  sensors::drive::reset();
  sensors::gyro::reset();
  rollers::speed(40);
  arm::speed(127);
  drive::speed(127);
  bar::speed(-127);
  while(sensors::arm::get() < 2950 || sensors::drive::get() < 400 || sensors::bar::get() < 700) {
    if(sensors::arm::get() > 2950) 
      arm::speed(5);
    if(sensors::drive::get() > 400) 
      drive::speed(0);
    if(sensors::bar::get() > 700) 
      bar::speed(15);
    delay(15);
  }
  arm::speed(0);
  drive::speed(0);
  bar::speed(0);
  wait(375);
  arm::speed(-127);
  wait(300);
  rollers::speed(-127);
  arm::speed(127);
  wait(200);

  if(strcmp(direction, "none")) {
    int dValue = -650;
    sensors::drive::reset();
    TaskHandle driveTask = taskCreate(drive::vDrive, TASK_DEFAULT_STACK_SIZE, (void*)dValue, TASK_PRIORITY_DEFAULT);
    wait(100);
    arm::speed(-127); bar::speed(127);
    while(sensors::arm::get() > 2200 || sensors::bar::get() > 1055) { 
      if(sensors::arm::get() < 2200) { 
        arm::speed(0);
      }
      if(sensors::bar::get() < 1055) { 
        bar::speed(0);
      }
      delay(15);
      delay(15);
    }
    arm::speed(0); bar::speed(0);
    while(sensors::drive::get() > -650) {
      delay(15); 
    }
    delay(250);
    taskDelete(driveTask);
    drive::speed(0);
    
    int rValue = ((strcmp(direction, "left")) ? 90 : (strcmp(direction, "right") ? -90 : 90));
    TaskHandle turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)rValue, TASK_PRIORITY_DEFAULT);
    while(abs(sensors::gyro::get()) < abs(rValue)) {
     delay(15);
    }
    delay(100);
    taskDelete(turnTask); 

    drive::speed(127);
    wait(500);
    drive::speed(0);
  }
}

void stationaryToMogo(char direction[]) {
  int dValue = -650;
  sensors::drive::reset();
  TaskHandle driveTask = taskCreate(drive::vDrive, TASK_DEFAULT_STACK_SIZE, (void*)dValue, TASK_PRIORITY_DEFAULT);
  wait(100);
  arm::speed(-127); bar::speed(127);
  while(sensors::arm::get() > 2200 || sensors::bar::get() > 1055) { 
    if(sensors::arm::get() < 2200) { 
      arm::speed(0);
    }
    if(sensors::bar::get() < 1055) { 
      bar::speed(0);
    }
    delay(15);
    delay(15);
  }
  arm::speed(0); bar::speed(0);
  while(sensors::drive::get() > -650) {
    delay(15); 
    printf("%d\n", sensors::drive::get());
  }
  delay(250);
  taskDelete(driveTask);
  drive::speed(0);
  
  int rValue = (strcmp(direction, "red") == 0) ? 90 : (strcmp(direction, "blue") == 0) ? -90 : 90;
  TaskHandle turnTask = taskCreate(drive::vRotate, TASK_DEFAULT_STACK_SIZE, (void*)rValue, TASK_PRIORITY_DEFAULT);
  while(abs(sensors::gyro::get()) < abs(rValue)) {
    delay(15);
    }
  delay(1000);
  taskDelete(turnTask); 
  mogoAutonMaster(1);
}


void autonomous() {
  mogoAutonMaster(1);
}
