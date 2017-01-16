//
//  movement.h
//  robot
//
//
#pragma once
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



#include "tacho.h"
#include "gyro.h"

//#include "globals.h"

//#define AZIMUT_ERROR 1


/**
 * \details Multi-purpose structure used to pass parameters to engine-related threads.
 */
typedef struct
{
  /** \details Relative angle displacement (may be not used in every thread). */
  int16_t angle;
  /** \details Run time parameter used for time-related threads for movement (may be not used in every thread). */
  uint16_t time;
  /** \details Speed parameter used in all the threads. Unit of measure is tacho_count per seconds. */
  int16_t speed;
  /** \details Distance displacement (may be not used in every thread). */
  int16_t distance;
  /** \details Tacho address set during initialization of all motors. */
  engine* tacho;
  /** \details Semaphore used for send only one command at a time (for each engine). */
  sem_t sem_engine;
}turn_engine_arg_struct;





//sem_t sem_right_engine, sem_left_engine;
//int8_t FLAG_adjust;  //pos: ... neg: ...

/**
 *  \details Turn one motor by a predefined angle
 *  \param  tacho Engine address.
 *  \param  angle Relative angle [in degrees].
 *  \param  speed Target speed (may be not reached). 
 */
inline void
turn_engine_by_angle(engine* tacho, int16_t angle, int16_t speed);


/**
 *  \details Turn on one motor for a predefined amount of time
 *  \param  tacho Engine address.
 *  \param  time  Run time.
 *  \param  speed Target speed (may be not reached).
 */
inline void
turn_engine_by_time(engine* tacho, uint16_t time, int16_t speed);


/**
 * \details Turn in place the robot by a fixed relative angle with respect
 *          to the head
 * \param angle[positive] Relative angle, turn right
 * \param angle[negative] Relative angle, turn left
 * \param speed           Target speed (may be not reached)  
 */
void
turn_inplace_by_relative_angle(int16_t angle, int16_t speed);

/**
 *  \details  Go straight for a predefined amount of time
 *  \param  time              Run time.
 *  \param  speed             Target speed (may be not reached).
 *  \param  check_orientation Boolean flag to enable orientation compensation if set to 1
 */
void
go_straight(uint16_t time, int16_t speed, FLAGS_T check_orientation);

/**
 *  \details  Go straight for a predefined distance
 *  \param  position          Target position
 *  \param  speed             Target speed (may be not reached).
 *  \param  check_orientation Boolean flag to enable orientation compensation if set to 1
 */
uint16_t
go_straight_dist(int16_t position, int16_t speed, FLAGS_T check_orientation);

/**
 *  \details  Go straight for a predefined distance while checking to do not touch obstacles 
 *            (max obstacle distance hardcoded in the function, i.e. 25 cm).
 *  \param  position  Target position.
 *  \param  speed     Target speed (may be not reached).
 */
void
go_straight_dist_obstacle(int16_t position, int16_t speed);

/**
 *  \details Stop all wheel-engines. Does not affect other motors (ARM for example).
 */
void
stop_engines(void);


void
go_to_position(int16_t x, int16_t y, int16_t speed);


void
move_by_offset(int16_t x_off, int16_t y_off, int16_t speed);


void *
__turn_inplace_by_relative_angle(void *arg);



/**
 *  \details Threaded version of \ref go_straight function
 */
void *
__go_straight(void* arg);

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


pthread_t
___go_straight(uint16_t time, int16_t speed);



void *
__go_straight_dist(void* arg);


pthread_t
___go_straight_dist(int16_t distance, int16_t speed);

//void* thread_check_azimut();

#define _movement_h
#endif /* movement_h */
