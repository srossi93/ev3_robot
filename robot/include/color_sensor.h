//
//  color_sensor.h
//  robot
//
//  Created by Simone Rossi on 07/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef color_sensor_h
#define color_sensor_h


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


#ifndef PTR
#define PTR
typedef uint8_t sensor_ptr;
#endif

/** Mutex for color sensor reading */
pthread_mutex_t color_mutex;
pthread_cond_t cv_ball_detected;

/** Structure for the sensor status */
typedef struct {

  /** Sensor address */
  sensor_ptr address;
  
  /** Reflection in % */
  int reflection;
}color_sensor;

/**
 * Read the reflection value from the color sensor
 * \param color color sensor struct 
 * \ret  reflection */
int read_reflection(color_sensor* color);

/**
 * Read all the value of the color sensor 
 * \param color color sensor struct */
void read_color_status(color_sensor* color);

/** Threaded version of \ref read_color_status */
void* __color_status_reader(void* color);




#ifndef _color_sensor_h
#define _color_sensor_h
#endif
#endif /* color_sensor_h */
