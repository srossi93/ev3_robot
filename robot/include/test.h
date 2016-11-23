//
//  test.h
//  robot
//
//  Created by Simone Rossi on 10/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef test_h
#define test_h

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
#include "movement.h"
#include "init.h"

#include "globals.h"

int test_turn_inplace_by_relative_angle();

#endif /* test_h */
