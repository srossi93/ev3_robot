//
//  movement.h
//  robot
//
//

#ifndef movement_h
#define movement_h

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

/** @param angle Relative angle
  *
  */
void
turn_by_relative_angle(uint16_t angle);



#endif /* movement_h */
