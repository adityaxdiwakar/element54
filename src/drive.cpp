#include "../include/drive.hpp"

namespace drive {
    motors frontLeft;
    motors frontRight;
    motors backLeft;
    motors backRight;

    void init(int motorNum, bool isReverse, bool isTruespeed, char location[]) {
        if(location == "frontLeft") {
            frontLeft.motorNum = motorNum;
            frontLeft.isReverse = isReverse;
            frontLeft.isTruespeed = isTruespeed;
        } else if(location == "frontRight") {
            frontRight.motorNum = motorNum;
            frontRight.isReverse = isReverse;
            frontRight.isTruespeed = isTruespeed;
        } else if(location == "backRight") {
            backRight.motorNum = motorNum;
            backRight.isReverse = isReverse;
            backRight.isTruespeed = isTruespeed;
        } else if(location == "backLeft") {
            backLeft.motorNum = motorNum;
            backLeft.isReverse = isReverse;
            backLeft.isTruespeed = isTruespeed;
        }
    }

    namespace forward {
        
    }
    }
}
