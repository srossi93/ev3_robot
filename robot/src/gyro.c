//
//  gyro.c
//  robot
//
//  Created by Simone Rossi on 24/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include <gyro.h>


int read_gyro_angle(gyro_sensor* gyro){
  int tmp;
  get_sensor_value(0, gyro->address, &tmp);
  return tmp;
}


int read_gyro_speed(gyro_sensor* gyro){
  int tmp;
  get_sensor_value(1, gyro->address, &tmp);
  return tmp;
}

void read_gyro_status(gyro_sensor* gyro){
  gyro->angle = read_gyro_angle(gyro);
  gyro->rot_speed = read_gyro_speed(gyro);
}

void* __gyro_status_reader(void* gyro){
  while (1) {
    pthread_mutex_lock(&gyro_mutex);
    read_gyro_status((gyro_sensor*)gyro);
    pthread_mutex_unlock(&gyro_mutex);
    msleep(10);
  }
}