//
//  globals.h
//  robot
//
//  Created by Simone Rossi on 23/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef globals_h
#define globals_h


#include "tacho.h"
#include "gyro.h"
#include "us_sensor.h"
#include "grabber.h"
#include "color_sensor.h"

engine engines[4];
gyro_sensor gyro[1];
us_sensor us[1];
color_sensor color[1];


pthread_t engines_status_reader_tid;
pthread_t gyro_status_reader_tid;
pthread_t us_status_reader_tid;
pthread_t color_status_reader_tid;

sem_t sem_right_engine, sem_left_engine;

pthread_mutex_t us_mutex;


#ifdef _grabber_h
extern ARM_STATUS arm_status;
#endif

#endif /* globals_h */
