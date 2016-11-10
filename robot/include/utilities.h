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
typedef uint8_t sensor_ptr;

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



#endif /* utilities_h */
