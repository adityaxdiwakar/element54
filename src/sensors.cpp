#include "../include/sensors.hpp"
#include "../include/main.h"

namespace sensors {
  namespace arm {
    int get() {
      return analogRead(ARM_SENSOR);
    }
  }
  namespace mogo {
    int get() {
      return analogRead(MOGO_SENSOR);
    }
  }
  namespace gyro {
    static bool gyro_is_initialized = false;
    static Gyro myGyro;

    int get() {
      if (!gyro_is_initialized) {
        gyro_is_initialized = true;
        myGyro = gyroInit(GYRO_M1, 0);
      }
      return (gyroGet(myGyro));
    }
    void reset() {
      gyroReset(myGyro);
    }
  }
  namespace bar {
    int get() {
      return analogRead(BAR_SENSOR);
    }
  }
  namespace drive {
    namespace left {
      static bool encL_is_initialized = false;
      static Encoder encL;

      int get() {
        if (!encL_is_initialized) {
          encL_is_initialized = true;
          encL = encoderInit(ENC_RT, ENC_RB, true);
        }
        return (encoderGet(encL));
      }
      void reset() {
        encoderReset(encL);
      }
    }
    namespace right {
      static bool encR_is_initialized = false;
      static Encoder encR;

      int get() {
        if (!encR_is_initialized) {
          encR_is_initialized = true;
          encR = encoderInit(ENC_LT, ENC_LB, true);
        }
        return (encoderGet(encR));
      }
      void reset() {
        encoderReset(encR);
      }
    }
    void reset() {
      left::reset();
      right::reset();
    }
    int get() {
      return((left::get() + right::get()) / 2);  
    }
  }
}