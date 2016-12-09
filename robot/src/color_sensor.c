//
//  color_sensor.c
//  robot
//
//  Created by Simone Rossi on 07/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "color_sensor.h"

int read_reflection(color_sensor* color)
{
  int tmp;
  get_sensor_value(0, color->address, &tmp);
  return tmp;
}

void read_color_status(color_sensor* color){
  int tmp = read_reflection(color);
  color->reflection = tmp;
}

void* __color_status_reader(void* color)
{

  while (1) {
    pthread_mutex_lock(&color_mutex);
    read_color_status((color_sensor*)color);
    
    //int tmp;
    //get_sensor_value(0, ((color_sensor*)color)->address, &tmp);
    //((color_sensor*)color)->reflection = tmp;
    
    //printf("From thread... Reflect: %d\n", tmp);
    
    //if (((color_sensor*)color)->reflection > 1)
    //{
      //printf("BAALLLLL\n");
      //pthread_cond_signal(&cv_ball_detected);
    //}
    pthread_mutex_unlock(&color_mutex);
    msleep(50);
  }
}