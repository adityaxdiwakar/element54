#include "API.h"


namespace sensors {
    namespace gyro {
        namespace main {
            int get();
        }
        namespace secondary {
            int get();
        }
        int getAvg();
        int get();
        void reset();
    }

    namespace drive {
        namespace left {
            int get(); }
        namespace right {
            int get(); }
        int get();
        void reset();
    }

    namespace arm {
        int get();
    }
    
    namespace mogo {
        int get();
    }

    namespace bar {
        int get();
    }
}