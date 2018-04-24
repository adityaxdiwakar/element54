#include "../include/sensors.hpp"

Gyro gyroMain;
Gyro gyroSecondary;
Encoder encLeft;
Encoder encRight;

namespace sensors {
    namespace gyro {
        bool mainInit = false;
        bool secondaryInit = false;
        namespace main {
            int get() {
                if(!mainInit) {
                    gyroMain = gyroInit(4, 0);
                    mainInit = true;
                }
                return(gyroGet(gyroMain));
            }
        }
        int get() {
            return(main::get());
        }
        void reset() {
            gyroReset(gyroMain);
        }
    }

    namespace drive {
        bool leftInit = false;
        bool rightInit = false;
        namespace left {
            int get() {
                if(!leftInit) {
                    encLeft = encoderInit(1, 2, true);
                    leftInit = true;
                }                
                return(encoderGet(encLeft));
            }
        }
        namespace right {
            int get() {
                if(!rightInit) {
                    encRight = encoderInit(3, 4, false);
                    rightInit = true;
                }                   
                return(encoderGet(encRight));
            }
        }
        int get() {
            return((left::get() + right::get()) / 2);
            }
        void reset() {
            encoderReset(encLeft);
            encoderReset(encRight);
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