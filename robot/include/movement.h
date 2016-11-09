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
#include <pthread.h>
#include <semaphore.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#include "utilities.h"

typedef struct
{
  int16_t angle;
  engine_ptr engine;
  uint8_t speed_mod;
  sem_t sem_engine;
}turn_engine_arg_struct;


sem_t sem_right_engine, sem_left_engine;

/**
 *  \details Turn one motor by a predefined angle
 *  \param angle Relative angle to move
 *  \param engine Motor ID
 *  \param speed_mod Speed modification parameter (speed = max / speed_mod)
 */
void
turn_engine(int16_t angle, engine_ptr engine, uint8_t speed_mod);

/**
 *  \details Threaded version of \ref turn_engine function
 */
void*
thread_turn_engine(void *arg);

/**
 * \details Turn in place the robot by a fixed relative angle with respect
 *          to the head
 * \param angle[positive] Relative angle, turn left
 * \param angle[negative] Relative angle, turn right
 * \param ID of the right engine
 * \param ID of the left engine
 */
void
turn_inplace_by_relative_angle(int16_t angle, engine_ptr right_engine, engine_ptr left_engine);

/**
 *  \details Identify the correct right and left engine
 *  \param[out] right_engine Will contain the pointer to the right engine
 *  \param[out] left_engine Will contain the pointer to the left engine
 *  \return 1 if successful, 0 otherwise
 */
int
identify_engines(engine_ptr *right_engine, engine_ptr *left_engine);



#endif /* movement_h */
