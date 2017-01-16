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


#define BEGINNER_RIGHT_START_X

#define BEGINNER_RIGHT_LEAVE_X 68
#define BEGINNER_RIGHT_LEAVE_Y 82

#define BEGINNER_RIGHT_END_X 100
#define BEGINNER_RIGHT_END_Y 180


void small_beginner(char starting_point);

#endif /* mjolnir_h */
