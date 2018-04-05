#include "../include/sensors.hpp"

Gyro gyroMain;
Gyro gyroSecondary;

namespace sensors {
    namespace gyro {
        bool mainInit;
        bool secondaryInit;
        namespace main {
            int get() {
                if(!mainInit) {
                    gyroMain = gyroInit(4, 0);
                }
                return(gyroGet(gyroMain));
            }
        }
        namespace secondary {
            int get() {
                if(!mainInit) {
                    gyroMain = gyroInit(4, 0);
                }
                return(gyroGet(gyroSecondary));
            }
        }
        int getAvg() {
            return((main::get() + secondary::get())/2);
        }
    }

    namespace arm {
        int armSensor = 3;
        int get() {
            return(analogRead(armSensor));
        }
    }
    
    namespace mogo {
        int mogoSensor = 1;
        int get() {
            return(analogRead(mogoSensor));
        }
    }

    namespace bar {
        int barSensor = 2;
        int get() {
            return(analogRead(barSensor));
        }
    }
}