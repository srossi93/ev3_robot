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

#define PI 3.1424
#define WHEEL_DIAMETER 5.61
#define TRACK 10
#define MOTOR_SCALE_FACTOR  (PI * WHEEL_DIAMETER) / 360
#define RAD(x) (x * PI) / 180

void reset_position();
void update_position();
void* __update_position();
void print_position();
float get_displacement(engine* motorR, engine* motorL);
int get_heading_from_gyro(gyro_sensor* gyro);
int get_heading_from_engines(engine* motorR, engine* motorL);
#endif /* odometry_h */
