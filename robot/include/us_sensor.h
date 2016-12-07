//
//  us_sensor.h
//  robot
//
//  Created by Simone Rossi on 06/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef us_sensor_h
#define us_sensor_h


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
//#include "globals.h"

#ifndef PTR
#define PTR
typedef uint8_t sensor_ptr;
#endif

pthread_mutex_t us_mutex;

typedef struct {
  
  sensor_ptr address;
  
  /** Distance in cm */
  int distance;

  
}us_sensor;

int read_us_distance(us_sensor* us);

void read_us_status(us_sensor* us);

void* __us_status_reader(void* us);

#endif /* gyro_h */
