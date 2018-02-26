#include "../include/joystick.hpp"

namespace joystick {
  int analog(Channel channel) {
    return joystickGetAnalog(1, channel);
  }

  bool digital(Group group, Button button) {
    return joystickGetDigital(1, group, button);
  }
} // namespace joystick