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

typedef struct
{
  int16_t angle;
  uint16_t time;
  int16_t speed;
  int16_t distance;
  engine* tacho;
  sem_t sem_engine;
}turn_engine_arg_struct;





//sem_t sem_right_engine, sem_left_engine;
//int8_t FLAG_adjust;  //pos: ... neg: ...

/**
 *  \details Turn one motor by a predefined angle
 */
inline void
turn_engine_by_angle(engine* tacho, int16_t angle, int16_t speed);

/**
 *  \details Turn one motor for a predefined time
 *  \param angle Time (milliseconds)
 *  \param engine Motor ID
 *  \param speed_mod Speed modification parameter (speed = max / speed_mod)
 */
inline void
turn_engine_by_time(engine* tacho, uint16_t time, int16_t speed);



/**
 * \details Turn in place the robot by a fixed relative angle with respect
 *          to the head
 * \param angle[positive] Relative angle, turn right
 * \param angle[negative] Relative angle, turn left
 */
void
turn_inplace_by_relative_angle(int16_t angle, int16_t speed);


void
go_straight(uint16_t time, int16_t speed, FLAGS_T check_orientation);


uint16_t
go_straight_dist(int16_t position, int16_t speed, FLAGS_T check_orientation);


void
stop_engines(void);


void
go_straight_dist_obstacle(int16_t position, int16_t speed);


void
go_to_position(int16_t x, int16_t y, int16_t speed);


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
