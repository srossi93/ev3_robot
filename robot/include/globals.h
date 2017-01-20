//
//  globals.h
//  robot
//
//  Created by Simone Rossi on 23/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//
#pragma once
#ifndef globals_h
#define globals_h


#include "tacho.h"
#include "gyro.h"
#include "us_sensor.h"
#include "grabber.h"
#include "color_sensor.h"
//#include "movement.h"

#define POW2(x) (x * x)
#ifndef PI
#define PI 3.1415
#endif

#define TO_DEG(x) x * 180 / PI

engine engines[4];
gyro_sensor gyro[1];
us_sensor us[1];
color_sensor color[1];


pthread_t engines_status_reader_tid;
pthread_t gyro_status_reader_tid;
pthread_t us_status_reader_tid;
pthread_t color_status_reader_tid;
pthread_t odometry_tid;

pthread_t read_bt_tid;
pthread_t write_bt_tid;

sem_t sem_right_engine, sem_left_engine;

pthread_mutex_t us_mutex;


//#ifdef _grabber_h
//extern ARM_STATUS arm_status;
//#endif

typedef enum {
  ARM_UP,
  ARM_DOWN,
  ARM_OPEN,
} ARM_STATUS;


#ifndef ROBOT_STATUS_TYPE
#define ROBOT_STATUS_TYPE 1
typedef enum {
  ROBOT_NOT_RUNNING,
  ROBOT_RUNNING
}ROBOT_STATUS;
#endif

extern ARM_STATUS arm_status;
extern ROBOT_STATUS robot_status;

typedef struct{
  float x;
  float y;
  int head;
}POSITION;

extern POSITION robot_position;


#endif /* globals_h */
