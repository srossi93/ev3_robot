//
//  grabber.c
//  robot
//
//  Created by Simone Rossi on 07/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "grabber.h"



void
deploy_arm(engine* arm, int16_t speed)
{
  if (arm_status == ARM_UP){
    log_to_file("Deploying arm...\n");
    turn_engine_by_angle(arm, -300, speed);
    log_to_file("--> Arm deployed\n");
    arm_status = ARM_DOWN;
  }
  return;
}

void
open_arm(engine* arm, int16_t speed)
{
  if (arm_status == ARM_DOWN){
    log_to_file("Opening arm...\n");
    turn_engine_by_angle(arm, -350, speed);
    log_to_file("--> Arm open\n");
    arm_status = ARM_OPEN;
  }
  return;
}

void
close_arm(engine* arm, int16_t speed)
{
  if (arm_status == ARM_OPEN){
    log_to_file("Closing arm...\n");
    turn_engine_by_angle(arm, +350, speed);
    log_to_file("--> Arm closed\n");
    arm_status = ARM_DOWN;
  }
  return;
}


void
undeploy_arm(engine* arm, int16_t speed)
{
  if (arm_status == ARM_DOWN){
    log_to_file("Undeploying arm...\n");
    turn_engine_by_angle(arm, +300, speed);
    log_to_file("--> Arm deployed\n");
    arm_status = ARM_UP;
  }
  return;
}




void grab_ball(engine* arm){
  
  do{
    deploy_arm(&engines[ARM], 500);
    
    do{
      open_arm(&engines[ARM], 300);
      
      
      pthread_t check_tid, run_tid;
      turn_engine_arg_struct arg;
      arg.time = 10000;
      arg.speed = 100;
      
      //pthread_create(&run_tid, NULL, __go_straight, (void*)&arg);
      //pthread_create(&check_tid, NULL, __check_ball, NULL);
      
      run_tid = ___go_straight(10000, 100);

      while (color->reflection < 5) ;
      
      pthread_cancel(run_tid);
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
      
      write_stop_action(&(engines[R]), TACHO_BRAKE);
      write_stop_action(&(engines[L]), TACHO_BRAKE);
      
      write_command(&(engines[R]), TACHO_STOP);
      write_command(&(engines[L]), TACHO_STOP);
      
      
      close_arm(&engines[ARM], 50);
      printf("color ref: %d\n", color->reflection);
    } while(color->reflection < 10);
    
    undeploy_arm(&engines[ARM], 500);
  } while (color->reflection < 10);
}


void release_ball(engine* arm, int16_t space){
  
  //turn_inplace_by_relative_angle(180, 100);
  
  deploy_arm(&engines[ARM], 500);
  
  open_arm(&engines[ARM], 20);
  
  go_straight_dist(-space, 200);
  
  close_arm(&engines[ARM], 500);
  undeploy_arm(&engines[ARM], 500);
  
  
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