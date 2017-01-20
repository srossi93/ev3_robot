//
//  mjolnir.h
//  robot
//
//  Created by Simone Rossi on 16/01/17.
//  Copyright © 2017 Simone Rossi. All rights reserved.
//

#ifndef mjolnir_h
#define mjolnir_h

#include "movement.h"
#include "utilities.h"
#include "init.h"
#include "tacho.h"
#include "globals.h"
#include "gyro.h"
#include "us_sensor.h"
#include "color_sensor.h"
#include "obstacle_detection.h"
#include "odometry.h"


#define BEGINNER_RIGHT_START_X    90
#define BEGINNER_RIGHT_START_Y    20

#define BEGINNER_RIGHT_LEAVE_X    60
#define BEGINNER_RIGHT_LEAVE_Y    85

#define BEGINNER_RIGHT_END_X      90
#define BEGINNER_RIGHT_END_Y      170

#define FINISHER_RIGHT_START_X    95
#define FINISHER_RIGHT_START_Y    170

#define FINISHER_RIGHT_SEARCH_X   68
#define FINISHER_RIGHT_SEARCH_Y   120

#define FINISHER_RIGHT_END_X      90
#define FINISHER_RIGHT_END_Y      20


#define BEGINNER_LEFT_START_X    30
#define BEGINNER_LEFT_START_Y    20

#define BEGINNER_LEFT_LEAVE_X    50
#define BEGINNER_LEFT_LEAVE_Y    80

#define BEGINNER_LEFT_END_X      30
#define BEGINNER_LEFT_END_Y      180

#define FINISHER_LEFT_START_X    30
#define FINISHER_LEFT_START_Y    180

#define FINISHER_LEFT_SEARCH_X   52
#define FINISHER_LEFT_SEARCH_Y   120

#define FINISHER_LEFT_END_X      30
#define FINISHER_LEFT_END_Y      20



#define BIG_BEGINNER_RIGHT_START_X  30
#define BIG_BEGINNER_RIGHT_START_Y  20

#define BIG_BEGINNER_RIGHT_POS1_X  90
#define BIG_BEGINNER_RIGHT_POS1_Y  120

#define BIG_BEGINNER_RIGHT_POS2_X  75
#define BIG_BEGINNER_RIGHT_POS2_Y  185

#define BIG_BEGINNER_RIGHT_POS3_X  30
#define BIG_BEGINNER_RIGHT_POS3_Y  235

#define BIG_BEGINNER_RIGHT_END_X  30
#define BIG_BEGINNER_RIGHT_END_Y  370

void small_beginner(char starting_point);
void small_finisher(char starting_point);

void big_beginner(char side, char starting_point);

typedef enum {
	NOTSTARTED,     /* Don't know its role yet. Waiting for instruction from server */
	STARTED,                /* Got its role, ready for run. */
	WAITING,                /* At its location, waiting for NEXT mesg to run */
	RUNNING,                /* On its journey */
	DONE,           /* When beginner or finisher completed its journey */
	KICKED,
	STOPPED
} robot_state;

extern int msgId;
extern robot_state gMyState;
extern unsigned char gMyRole, gMySide, gTeamMateId;

#endif /* mjolnir_h */
