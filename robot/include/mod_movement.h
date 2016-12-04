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

#define RIGHT_MOTOR_PORT "outC"
#define LEFT_MOTOR_PORT "outB"
#define ARM_MOTOR_PORT "outD"

/**
 * GLOBAL VARIABLES
 */
int left_motor_id, right_motor_id, arm_motor_id;

/**
 * FUNCTIONS DECLERATIONS
 */

/* Go straight with specified time */
void mod_mov_go_straight_timed(uint32_t time);

/* Go straight with specified position */
void mod_mov_go_straight_pos(uint32_t distance);

/* Go straight with mode (timed/position) */
void mod_mov_go_straight(uint8_t mode, uint32_t value);

/* Turn left in place */
void mod_mov_turn_left_in_place(void);

/* Turn left normal (one wheel move) */
void mod_mov_turn_left_normal(void);

/* Turn left with mode (in place/normal) */
void mod_mov_turn_left(uint8_t mode);

/* Turn right in place */
void mod_mov_turn_right_in_place(void);

/* Turn right normal (one wheel move) */
void mod_mov_turn_right_normal(void);

/* Turn right with mode (in place/normal) */
void mod_mov_turn_right(uint8_t mode);

/* Turn around 180 degrees to the left */
void mod_mov_turn_around_left(void);

/* Turn around 180 degrees to the right */
void mod_mov_turn_around_right(void);

/* Turn around with modes (in place/normal, left/right) */
void mod_mov_turn_around(uint8_t mode, uint8_t direction);

/* Important: align with borders */
void mod_mov_align_with_borders(void);




/**
 * Temporary: testing phase. Will be removed.
 */
void test_motor(uint8_t sn);

void MOVE(uint8_t motor_id, int32_t value);

void STOP(uint8_t motor_id);

void STOP_ALL(void);

void TURN_LEFT(void);

void TURN_RIGHT(void);

void TURN_AROUND(void);

void GO_STRAIGHT(uint32_t distance); 

#endif /* MJOLNIR_MOD_MOV_H */
