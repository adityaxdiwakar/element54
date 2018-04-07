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