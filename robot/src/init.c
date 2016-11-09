//
//  init.c
//  robot
//
//  Created by Simone Rossi on 08/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "init.h"

extern char msg[255];

int
robot_init(void)
{
  sprintf(msg, "*** Initialization ***\n");
  log_to_file(msg);

  if ( ev3_init() != 1 )
  {
    sprintf(msg, "Initialization failed\n");
    log_to_file(msg);
    return 0;
  }

  while (ev3_tacho_init() < 1)
  {
    sprintf(msg, "Motor initialization failed. Waiting for tacho motors\n");
    log_to_file(msg);
    msleep(1000);
  }
  
  if ( ev3_sensor_init() == -1 )
  {
    sprintf(msg, "Sensor initialization failed\n");
    log_to_file(msg);
    return 0;
  }
  
  return 1;
}