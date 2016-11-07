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

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

void
identify_engines(uint8_t *engine1, uint8_t *engine2, uint8_t *right_engine, uint8_t *left_engine);


#endif /* utilities_h */
