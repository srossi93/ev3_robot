//
//  init.h
//  robot
//
//  Created by Simone Rossi on 08/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef init_h
#define init_h


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

#include "tacho.h"
#include "utilities.h"

engine engines[4];

pthread_t engine_manager_tid;

/**
 *  \details Performs robot initialization (both motors and sensors)
 *  \return 1 if successfull, 0 if errors occured
 */
int
robot_init(void);


int engines_init(void);

void robot_deinit(void);

#endif /* init_h */
