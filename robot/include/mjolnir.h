//
//  mjolnir.h
//  Main header file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 09/11/16.
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#ifndef MJOLNIR_H
#define MJOLNIR_H

#include <stdio.h>
#include <string.h>
#include "ev3.h"
#include "ev3_port.h"

#if 1
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#endif

// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif

typedef enum {
	NOTSTARTED,	/* Don't know its role yet. Waiting for instruction from server */
	STARTED,		/* Got its role, ready for run. */
	WAITING,		/* At its location, waiting for NEXT mesg to run */
	RUNNING,		/* On its journey */ 
	DONE,		/* When beginner or finisher completed its journey */
	STOPPED
} robot_state;

extern int msgId;
extern robot_state gMyState;
extern unsigned char gMyRole, gMySide, gTeamMateId;

#endif /* MJOLNIR_H */
