//
//  gyro.c
//  robot
//
//  Created by Simone Rossi on 24/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include <gyro.h>
#define EVALUATIONS 10

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
  int sum = 0;
  int i = 0;
  for (; i<EVALUATIONS; i++) {
    int tmp = read_gyro_angle(gyro);
    if (!ev3_search_sensor(LEGO_EV3_GYRO, &gyro->address, 0)) return;
    if (abs(tmp) > 30000000) return;
    sum += tmp;

  }
  //int tmp = read_gyro_angle(gyro);
  //if (!ev3_search_sensor(LEGO_EV3_GYRO, &gyro->address, 0)) return;
  //if (abs(tmp) > 30000000) return;
  gyro->angle = sum / EVALUATIONS;
  gyro->rot_speed = read_gyro_speed(gyro);

}

void* __gyro_status_reader(void* gyro){
  while (1) {
    pthread_mutex_lock(&gyro_mutex);
    read_gyro_status((gyro_sensor*)gyro);
    pthread_mutex_unlock(&gyro_mutex);
    msleep(50);
  }
}