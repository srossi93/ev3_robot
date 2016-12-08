//
//  gyro.h
//  robot
//
//  Created by Simone Rossi on 23/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef gyro_h
#define gyro_h

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

pthread_mutex_t gyro_mutex;

typedef struct {
  
  sensor_ptr address;
  
  /**  Angle in deg (-32768 to 32767) */
  int angle;
  /**  Rotational Speed in deg/s(-440 to 440) */
  int rot_speed;
  
}gyro_sensor;

int read_gyro_angle(gyro_sensor* gyro);
int read_gyro_speed(gyro_sensor* gyro);

void read_gyro_status(gyro_sensor* gyro);

void* __gyro_status_reader(void* gyro);

#endif /* gyro_h */
