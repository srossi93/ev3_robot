//
//  utilities.h
//  robot
//
//  Created by Simone Rossi on 07/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef utilities_h
#define utilities_h

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#define msleep(msec) usleep(msec*1000)
typedef uint8_t engine_ptr;
char msg[255];

/**
 *  \details ...
 */
char*
time_stamp();


/**
 *  \details Append the message in a file called "log.txt"
 *           If it does not exist, it will be created
 */
void
log_to_file(char *msg);

/**
 *  \details Identify the correct right and left engine
 *  \param right_engine Will contain the pointer to the right engine
 *  \param left_engine Will contain the pointer to the left engine
 *  \return 1 if successful, 0 otherwise
 */
int
identify_engines(engine_ptr *right_engine, engine_ptr *left_engine);


#endif /* utilities_h */
