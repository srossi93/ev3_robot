//
//  mjolnir_tacho.h
//  Tacho motors header file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 09/11/16.
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#ifndef MJOLNIR_TACHO_H
#define MJOLNIR_TACHO_H

#include <mjolnir.h>
#include "ev3_tacho.h"

/ **
  * Functions definitions
  */
void test_motor(uint8_t sn);

void MOVE(uint8_t motor_id, uint32_t time);

void STOP(uint8_t motor_id);

void STOP_ALL(void);

void TURN_LEFT(void);

void TURN_RIGHT(void);

void TURN_AROUND(void);

void GO_STRAIGHT(uint32_t time); 

#endif /* MJOLNIR_TACHO_H */
