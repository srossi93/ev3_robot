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

engine engines[4];
gyro_sensor gyro[1];

pthread_t engines_status_reader_tid;
pthread_t gyro_status_reader_tid;

sem_t sem_right_engine, sem_left_engine;

#endif /* globals_h */
