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
#include <sys/time.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#include "utilities.h"

#include "globals.h"

#include "tacho.h"
#include "gyro.h"

#define AZIMUT_ERROR 1

typedef struct
{
  int16_t angle;
  uint16_t time;
  uint16_t speed;
  engine* tacho;
  sem_t sem_engine;
}turn_engine_arg_struct;


//sem_t sem_right_engine, sem_left_engine;
//int8_t FLAG_adjust;  //pos: ... neg: ...

/**
 *  \details Turn one motor by a predefined angle
 */
inline void
turn_engine_by_angle(engine* tacho, int16_t angle, uint16_t speed);

/**
 *  \details Turn one motor for a predefined time
 *  \param angle Time (milliseconds)
 *  \param engine Motor ID
 *  \param speed_mod Speed modification parameter (speed = max / speed_mod)
 */
inline void
turn_engine_by_time(engine* tacho, uint16_t time, uint8_t speed);

/**
 *  \details Threaded version of \ref turn_engine function
 */
void*
__turn_engine_by_angle(void *arg);

/**
 *  \details Threaded version of \ref turn_engine function
 */
void*
__turn_engine_by_time(void *arg);

/**
 * \details Turn in place the robot by a fixed relative angle with respect
 *          to the head
 * \param angle[positive] Relative angle, turn right
 * \param angle[negative] Relative angle, turn left
 */
void
turn_inplace_by_relative_angle(int16_t angle, uint16_t speed);

/**
 *  \details Identify the correct right and left engine
 *  \param[out] right_engine Will contain the pointer to the right engine
 *  \param[out] left_engine Will contain the pointer to the left engine
 *  \return 1 if successful, 0 otherwise
 */
int
identify_engines(engine_ptr *right_engine, engine_ptr *left_engine);

void
go_straight(uint16_t time, uint16_t speed);

void* thread_check_azimut();


#endif /* movement_h */
