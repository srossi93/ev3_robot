//
//  odometry.h
//  robot
//
//  Created by Simone Rossi on 13/01/17.
//  Copyright © 2017 Simone Rossi. All rights reserved.
//

#ifndef odometry_h
#define odometry_h

#include "tacho.h"
#include "globals.h"

#define PI 3.14
#define WHEEL_DIAMETER 5.61
#define MOTOR_SCALE_FACTOR  (PI * WHEEL_DIAMETER) / engines[R].count_per_rot

void reset_position();
float get_displacement(engine* motorR, engine* motorL);
int get_heading(gyro_sensor* gyro);
#endif /* odometry_h */
