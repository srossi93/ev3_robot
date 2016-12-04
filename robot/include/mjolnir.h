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

#endif /* MJOLNIR_H */
