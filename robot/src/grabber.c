//
//  grabber.c
//  robot
//
//  Created by Simone Rossi on 07/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "grabber.h"
#include "globals.h"


void
deploy_arm(engine* arm, int16_t speed) {
  if (arm_status == ARM_UP){
    log_to_file("Deploying arm...\n");
    turn_engine_by_angle(arm, -250, speed);
    log_to_file("--> Arm deployed\n");
    arm_status = ARM_DOWN;
  }
  return;
}

void
open_arm(engine* arm, int16_t speed) {
  if (arm_status == ARM_DOWN){
    log_to_file("Opening arm...\n");
    turn_engine_by_angle(arm, -325, speed);
    log_to_file("--> Arm open\n");
    arm_status = ARM_OPEN;
  }
  return;
}

void
close_arm(engine* arm, int16_t speed) {
  if (arm_status == ARM_OPEN){
    log_to_file("Closing arm...\n");
    turn_engine_by_angle(arm, +325, speed);
    log_to_file("--> Arm closed\n");
    arm_status = ARM_DOWN;
  }
  return;
}

void
undeploy_arm(engine* arm, int16_t speed) {
  if (arm_status == ARM_DOWN){
    log_to_file("Undeploying arm...\n");
    turn_engine_by_angle(arm, +250, speed);
    log_to_file("--> Arm deployed\n");
    arm_status = ARM_UP;
  }
  return;
}

int
grab_ball(engine* arm, int ball_distance){

  int time = 0;
  //int ball_distance = us->distance;
  do{
    //deploy_arm(&engines[ARM], 500);
    //open_arm(&engines[ARM], 300);
    log_to_file("Deploying arm...\n");
    turn_engine_by_angle(arm, -575, 400);
    log_to_file("--> Arm deployed\n");
    arm_status = ARM_OPEN;
      //pthread_t check_tid, run_tid;
      //turn_engine_arg_struct arg;
      //arg.distance = 10;
      //arg.speed = 50;
      
      //pthread_create(&run_tid, NULL, __go_straight_dist, (void*)&arg);
      //pthread_create(&check_tid, NULL, __check_ball, NULL);
      
      //run_tid = ___go_straight_dist(10, 50);
      
      //int tot_time = go_straight_dist(20, 100, 0);
      //go_straight_dist(us->distance/4, 100, 1);
      //go_straight(5000, 50, 0);

    //go_straight_dist(ball_distance, 50, 0);  //<<<<<<<<<<<
    pthread_t tid;
    turn_engine_arg_struct arg;
    arg.distance = ball_distance;
    arg.speed = 50;
    pthread_create(&tid, NULL, __go_straight_dist, (void*)&arg);
    
    printf("Detection...\n");
    //  time+=250;
    msleep(250);
    while ((color->reflection < 4) && robot_status == ROBOT_RUNNING) {
      if (robot_status == ROBOT_NOT_RUNNING) pthread_cancel(tid);
      msleep(250);
    }
    stop_engines();
    pthread_join(tid, NULL);


      //int i;
      //for (i = 0; i < 10000; i+=250) {
        //if (ball_found) {
          //msleep(250);
          //log_to_file("BALL detected\n");
          //pthread_cancel(run_tid);
          //break;
        //}
      //}
      
      //pthread_join(run_tid, NULL);
      //pthread_cancel(check_tid);
    
    
    
    //close_arm(&engines[ARM], 250);
      //printf("color ref: %d\n", color->reflection);
      //undeploy_arm(&engines[ARM], 500);
    log_to_file("Undeploying arm...\n");
    turn_engine_by_angle(arm, +575, 500);
    log_to_file("--> Arm undeployed\n");
    arm_status = ARM_UP;
    
  } while (color->reflection < 4);
  
  return time;
}

void
release_ball(engine* arm, int16_t space){
  
  //turn_inplace_by_relative_angle(180, 100);
  
  deploy_arm(&engines[ARM], 500);
  
  open_arm(&engines[ARM], 100);
  
  go_straight_dist(-space, 100, 0);

  msleep(1000);
  //close_arm(&engines[ARM], 500);
  //undeploy_arm(&engines[ARM], 500);
  log_to_file("Undeploying arm...\n");
  turn_engine_by_angle(arm, +575, 500);
  log_to_file("--> Arm undeployed\n");
  
}

void
search_and_grab(engine* arm){
  int span[] = {80, 60};
  int distance[200];
  int orientation[200];
  
  int min_position, num_of_observations, min_orientation, min_distance = 0;
  int j = 0;
  
  for (j = 0; j < 2; j++) {
    
    min_distance = distance[0];
    min_position = 0;
    num_of_observations = 0;
    min_orientation = 0;
    
    int i = 0;
    for (i = 0; i < 200; i++) {
      distance[i] = 3000;
    }
    
    turn_inplace_by_relative_angle(-span[j]/2, 500);
    
    pthread_t tid;
    turn_engine_arg_struct arg;
    arg.angle = span[j];
    //arg.speed = 20;
    arg.speed = 100;
    
    pthread_create(&tid, NULL, __turn_inplace_by_relative_angle, (void*)&arg);
    msleep(100);
    
    i = 0;
    for (i = 0; i < 200; i++) {
      if (robot_status != ROBOT_RUNNING) {
        break;
      }
      distance[i] = us->distance;
      orientation[i] = gyro->angle;
      //printf("%d\n", us->distance);
      msleep(50);
    }
    
    min_distance = distance[0];
    min_position = 0;
    num_of_observations = 0;
    
    for (i = 0; i < 200; i++){
      if (distance[i] == 3000) {
        break;
      }
      //printf("%d: %d\n", i, distance[i]);
      if (distance[i] <= min_distance){
        min_distance = distance[i];
        min_orientation = orientation[i];
        min_position = i;
      }
      num_of_observations++;
    }
    
    printf("Min distance: %d\nPosition: %d\nNum of obs: %d\nOrientation: %d\n", min_distance, min_position, num_of_observations, min_orientation);
    
    //turn_inplace_by_relative_angle(-90+4.2*min_position/2, 100);
    turn_inplace_by_relative_angle(-(gyro->angle - min_orientation), 100);
    
    if (min_distance < 250) {
      continue;
    }
    go_straight_dist(10, 200, 1);
    
  }
  
  if (min_distance > 350) {
    return;
  }
  
  
  grab_ball(arm, min_distance/10-4);

}


/*****************************************************
                THREAD FUNCTIONS
******************************************************/

void* __check_ball()
{
  ball_found = 0;

  while (1) {
    msleep(250);
    pthread_mutex_lock(&color_mutex);
    //printf("light: %d\n", color->reflection);
    if (color->reflection > 4)
    {
      printf("light: %d\n", color->reflection);
      ball_found = 1;

    }
    pthread_mutex_unlock(&color_mutex);
  }
}