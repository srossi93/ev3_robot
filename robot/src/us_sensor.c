//
//  us_sensor.c
//  robot
//
//  Created by Simone Rossi on 06/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "us_sensor.h"


int read_us_distance(us_sensor* us){
  int tmp;
  get_sensor_value(0, us->address, &tmp);
  return tmp;
}

void read_us_status(us_sensor* us){
  us->distance = read_us_distance(us);
}

void* __us_status_reader(void* us){
  while (1) {
    pthread_mutex_lock(&us_mutex);
      read_us_status((us_sensor*)us);
    pthread_mutex_unlock(&us_mutex);
    msleep(10);
  }

}