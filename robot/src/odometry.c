//
//  odometry.c
//  robot
//
//  Created by Simone Rossi on 13/01/17.
//  Copyright © 2017 Simone Rossi. All rights reserved.
//

#include <stdio.h>
#include "odometry.h"
#include <math.h>

int previous_displacement_L = 0;
int previous_displacement_R = 0;
int previous_rotation_L = 0;
int previous_rotation_R = 0;
int previous_angle = 0;
int previous_heading_engines = 90;
int previous_heading = 90;

void reset_position(){
  robot_position.x = 0;
  robot_position.y = 0;
}

float get_displacement(engine* motorR, engine* motorL){
  int positionR, positionL;
  positionR = motorR->position;
  positionL = motorL->position;
  
  //printf("PreviousPositionL: %d\nPreviousPositionR%d\nPositionL: %d\nPositionR:%d\n\n", previous_displacement_L, previous_displacement_R, positionL, positionR);
  
  float displacement = ((positionR + positionL - previous_displacement_L - previous_displacement_R) * PI * WHEEL_DIAMETER) / 720;//motorR->count_per_rot / 2;
  
  //printf("%f\n\n",displacement);
  
  previous_displacement_L = positionL;
  previous_displacement_R = positionR;
  
  return displacement;
}

int get_heading_from_gyro(gyro_sensor* gyro){
  int heading;
  //printf("angle: %d\n",gyro->angle);
  heading =  previous_heading + (previous_angle - gyro->angle);
  previous_angle = gyro->angle;
  previous_heading = heading;
  return heading;
}

//int get_heading_from_engines(engine* motorR, engine* motorL){
  //int heading;
  //int positionR, positionL;
  //positionR = motorR->position;
  //positionL = motorL->position;
  ////printf("HEADING\n");
  ////printf("PositionL: %d\nPositionR:%d\n\n", positionL, positionR);
  
  //if (abs(positionL - previous_rotation_L) < 5)
    //return heading;

  //if (abs(positionR - previous_rotation_R) < 5)
    //return heading;
  
  //heading =  previous_heading - (((positionR - positionL - previous_rotation_R + previous_rotation_L) * PI * WHEEL_DIAMETER) / 720 ) * TRACK;

  ////previous_heading_engines = heading;
  //previous_rotation_R = positionR;
  //previous_rotation_L = positionL;
  
  //return heading;
  
//}

void update_position(){
  float displacement = get_displacement(&engines[R], &engines[L]);
  //int heading = get_heading_from_gyro(gyro);
  int heading = get_heading_from_gyro(gyro);
  //printf("DISP: %f\nHEAD: %d\n", displacement, heading);
  previous_heading = heading;
  robot_position.x += displacement * (float)cos(RAD(heading));
  robot_position.y += displacement * (float)sin(RAD(heading));
  robot_position.head = heading;
 
}

int is_inside(){
  if (robot_position.x > SMALL_ARENA_MAX_X)
    return 0;
  if (robot_position.y > SMALL_ARENA_MAX_Y)
    return 0;
  return 1;
}

void* __update_position(){
  reset_position();
  //print_position();
  while (1) {
    msleep(500);
    update_position();
    //print_position();
  }
}


void print_position(){
  printf("X   :\t%f\nY   :\t%f\nHEAD:\t%d\n\n", robot_position.x, robot_position.y, robot_position.head);
}