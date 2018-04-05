#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "API.h"

/** The joystick class */
namespace joystick {
  /** A group of buttons on the joystick */
  typedef unsigned char Group;

  /** An analog channel on the joystick */
  typedef unsigned char Channel;

  /** A set of buttons within a group */
  typedef enum {
    Up    = JOY_UP,
    Down  = JOY_DOWN,
    Left  = JOY_LEFT,
    Right = JOY_RIGHT,
  } Button;

  /** Get the analog value of the specified channel */
  int analog(Channel channel);

  /** Returns whether or not a button in a group is pressed */
  bool digital(Group group, Button button);
}; // namespace joystick

#endif /* end of include guard: JOYSTICK_H */
