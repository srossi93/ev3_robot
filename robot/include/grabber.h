//
//  grabber.h
//  robot
//
//  Created by Simone Rossi on 07/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef grabber_h
#define grabber_h

#include "movement.h"


//typedef enum {
  //ARM_UP,
  //ARM_DOWN,
  //ARM_OPEN,
//} ARM_STATUS;

//ARM_STATUS arm_status;

FLAGS_T ball_found;

void deploy_arm(engine* arm, int16_t speed);
void open_arm(engine* arm, int16_t speed);
void close_arm(engine* arm, int16_t speed);
void undeploy_arm(engine* arm, int16_t speed);


int grab_ball(engine* arm);
void release_ball(engine* arm, int16_t space);

void* __check_ball();

#define _grabber_h
#endif /* grabber_h */
