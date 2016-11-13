//
//  mod_movement.h
//  Movement module header file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 13/11/16.
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#ifndef MJOLNIR_MOD_MOV_H
#define MJOLNIR_MOD_MOV_H

#include <mjolnir.h>
#include "ev3_tacho.h"

/**
 * ENUM DECLERATION
 */

/**
 * FUNCTIONS DECLERATIONS
 */

/* Go straight with specified time */
mod_mov_go_straight_timed(unint32_t time);

/* Go straight with specified position */
mod_mov_go_straight_pos(uint32_t distance);

/* Go straight with mode (timed/position) */
mod_mov_go_straight(uint8_t mode, uint32_t value);

/* Turn left in place */
mod_mov_turn_left_in_place(void);

/* Turn left normal (one wheel move) */
mod_mov_turn_left_normal(void);

/* Turn left with mode (in place/normal) */
mod_mov_turn_left(uint8_t mode);

/* Turn right in place */
mod_mov_turn_right_in_place(void);

/* Turn right normal (one wheel move) */
mod_mov_turn_right_normal(void);

/* Turn right with mode (in place/normal) */
mod_mov_turn_right(uint8_t mode);

/* Turn around 180 degrees to the left */
mod_mov_turn_around_left(void);

/* Turn around 180 degrees to the right */
mod_mov_turn_around_right(void);

/* Turn around with modes (in place/normal, left/right) */
mod_mov_turn_around(uint8_t mode, uint8_t direction);

/* Important: align with borders */
mod_mov_align_with_borders(void);




/**
 * Temporary: testing phase. Will be removed.
 */
void test_motor(uint8_t sn);

void MOVE(uint8_t motor_id, uint32_t time);

void STOP(uint8_t motor_id);

void STOP_ALL(void);

void TURN_LEFT(void);

void TURN_RIGHT(void);

void TURN_AROUND(void);

void GO_STRAIGHT(uint32_t time); 

#endif /* MJOLNIR_MOD_MOV_H */
