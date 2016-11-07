//
//  utilities.c
//  robot
//
//  Created by Simone Rossi on 07/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include <stdio.h>

#include <unistd.h>
#include <stdint.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

void
identify_engines(uint8_t *right_engine, uint8_t *left_engine)
{
  int max_speed = 5;
  uint8_t gyro_sensor_id;
  uint8_t engine1, engine2;
  int32_t initial_absolute_angle = 0;
  int32_t final_absolute_angle = 0;
  
  if (! ev3_search_tacho( LEGO_EV3_L_MOTOR, &engine1, 0 ))
    return;
  
  if (! ev3_search_tacho( LEGO_EV3_L_MOTOR, &engine2, engine1+1 ))
    return;
  
  if( !ev3_search_sensor(LEGO_EV3_GYRO, &gyro_sensor_id, 0))
  {
    printf("Gyro sensor not found...\n");
    return;
  }

  printf("motor1: %d\nmotor2: %d\n",engine1, engine2); 

  get_sensor_value(0, gyro_sensor_id, &initial_absolute_angle);
  printf("[GYRO] : Initial absolute value %d\n", initial_absolute_angle);

  get_tacho_max_speed( engine1, &max_speed );
  set_tacho_speed_sp( engine1, max_speed / 2 );
  set_tacho_ramp_up_sp( engine1, 0 );
  set_tacho_ramp_down_sp( engine1, 0 );
  set_tacho_position_sp( engine1, 90 );
  set_tacho_command_inx( engine1, TACHO_RUN_TO_REL_POS );
  
  usleep(1000*1000); 
  get_sensor_value(0, gyro_sensor_id, &final_absolute_angle);
  printf("[GYRO] : Final absolute value %d\n", final_absolute_angle);

  get_tacho_max_speed( engine1, &max_speed );
  set_tacho_speed_sp( engine1, max_speed / 2 );
  set_tacho_ramp_up_sp( engine1, 0 );
  set_tacho_ramp_down_sp( engine1, 0 );
  set_tacho_position_sp( engine1, -90 );
  set_tacho_command_inx( engine1, TACHO_RUN_TO_REL_POS );
  
  if ((final_absolute_angle - initial_absolute_angle) < 0)
  {
    *right_engine = engine1;
    *left_engine = engine2;
  }
  else
  {
    *right_engine = engine2;
    *left_engine = engine1;
  }
  
}
