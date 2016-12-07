//
//  grabber.c
//  robot
//
//  Created by Simone Rossi on 07/12/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "grabber.h"

void
deploy_arm(engine* engine)
{
  if (arm_status == ARM_UP){
    log_to_file("Deploying arm...\n");
    turn_engine_by_angle(engine, -250, 300);
    log_to_file("*** Arm deployed\n");
    arm_status = ARM_DOWN;
  }
  return;
}

void
open_arm(engine* engine)
{
  if (arm_status == ARM_DOWN){
    log_to_file("Opening arm...\n");
    turn_engine_by_angle(engine, -250, 50);
    log_to_file("*** Arm open\n");
    arm_status = ARM_OPEN;
  }
  return;
}

void
close_arm(engine* engine)
{
  if (arm_status == ARM_OPEN){
    log_to_file("Closing arm...\n");
    turn_engine_by_angle(engine, +250, 50);
    log_to_file("*** Arm closed\n");
    arm_status = ARM_DOWN;
  }
  return;
}


void
undeploy_arm(engine* engine)
{
  if (arm_status == ARM_DOWN){
    log_to_file("Undeploying arm...\n");
    turn_engine_by_angle(engine, +250, 300);
    log_to_file("*** Arm deployed\n");
    arm_status = ARM_UP;
  }
  return;
}