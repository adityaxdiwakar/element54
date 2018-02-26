#ifndef SENSORS_H
#define SENSORS_H
#include "API.h"

namespace sensors {
    namespace arm {
        int get();
    }
    namespace mogo {
        int get();
    }
    namespace bar {
        int get();
    }
    namespace gyro {
        int get();
        void reset();
    }
    namespace drive {
        namespace left {
            void reset();
            int get();
        }
        namespace right {
            void reset();
            int get();
        }
        void reset();
        int get();
    }
}

#endif