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

#include "utilities.h"

/** @param angle Relative angle
  *
  */
void
turn_by_relative_angle(uint16_t angle);

/**
 *  \details Identify the correct right and left engine
 *  \param right_engine Will contain the pointer to the right engine
 *  \param left_engine Will contain the pointer to the left engine
 *  \return 1 if successful, 0 otherwise
 */
int
identify_engines(engine_ptr *right_engine, engine_ptr *left_engine);



#endif /* movement_h */
