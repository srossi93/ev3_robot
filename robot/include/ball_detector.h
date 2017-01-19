//
//  us_sensor.h
//  robot
//
//  Created by Simone Rossi on 06/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef ball_detector_h
#define ball_detector_h


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

int ball_detect(int dist);

#endif /* ball_detector */
