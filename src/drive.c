#include <MotorDef.h>
#include <API.h>
#include <drive.h>

void driveSet(int left, int right) {
  motorSet(Base_FL, left);
  motorSet(Base_BL, -left);
  motorSet(Base_BR, right);
  motorSet(Base_FR, -right);
}
