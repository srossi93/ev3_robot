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


typedef enum {
  ARM_UP,
  ARM_DOWN,
  ARM_OPEN,
} ARM_STATUS;

ARM_STATUS arm_status;

void deploy_arm(engine* engine);
void open_arm(engine* engine);
void close_arm(engine* engine);
void undeploy_arm(engine* engine);
#define _grabber_h
#endif /* grabber_h */
