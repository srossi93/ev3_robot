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

/** \param angle[positive] Relative angle, turn left
  * \param angle[negative] Relative angle, turn right
  * \param ID of the right engine
  * \param ID of the left engine
  */
void
turn_by_relative_angle(uint8_t angle, engine_ptr right_engine, engine_ptr left_engine);

/**
 *  \details Identify the correct right and left engine
 *  \param[out] right_engine Will contain the pointer to the right engine
 *  \param[out] left_engine Will contain the pointer to the left engine
 *  \return 1 if successful, 0 otherwise
 */
int
identify_engines(engine_ptr *right_engine, engine_ptr *left_engine);



#endif /* movement_h */
