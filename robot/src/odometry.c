//
//  odometry.c
//  robot
//
//  Created by Simone Rossi on 13/01/17.
//  Copyright © 2017 Simone Rossi. All rights reserved.
//

#include <stdio.h>
#include "odometry.h"


int previous_displacement_L = 0;
int previous_displacement_R = 0;
int previous_heading = 90;

void reset_position(){
  robot_position.x = 0;
  robot_position.y = 0;
}

float get_displacement(engine* motorR, engine* motorL){
  float displacement = ((motorR->position + motorL->position - previous_displacement_L - previous_displacement_R) * PI * WHEEL_DIAMETER) / motorR->count_per_rot / 2;
  
  previous_displacement_L = motorR->position;
  previous_displacement_R = motorL->position;
  
  return displacement;
}

int get_heading(gyro_sensor* gyro){
  int heading;
  heading =  previous_heading - gyro->angle;
  previous_heading = heading;
  return heading;
}