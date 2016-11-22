//
//  init.c
//  robot
//
//  Created by Simone Rossi on 08/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "init.h"

extern char msg[255];
extern sem_t sem_right_engine, sem_left_engine;

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

  sem_init(&sem_right_engine, 0, 1);
  sem_init(&sem_left_engine, 0, 1);
  
  engines_init();

  return 1;
}

int engines_init(void)
{
  int max_speed;
  uint8_t gyro_sensor_id;
  engine_ptr engine1, engine2;
  int32_t initial_absolute_angle = 0;
  int32_t final_absolute_angle = 0;
  
  
  sprintf(msg, "*** Start engine identification ***\n");
  log_to_file(msg);
  
  // Search the first engine
  if ( !ev3_search_tacho(LEGO_EV3_L_MOTOR, &engine1, 0) )
  {
    sprintf(msg, " --> No LEGO_EV3_L_MOTOR found\n\tAborting...\n");
    log_to_file(msg);
    return 0;
  }
  
  // Search the second engine
  if ( !ev3_search_tacho(LEGO_EV3_L_MOTOR, &engine2, engine1 + 1) )
  {
    sprintf(msg, " --> No second LEGO_EV3_L_MOTOR found\n\tAborting...\n");
    log_to_file(msg);
    return 0;
  }
  
  // Search the gyroscope
  if( !ev3_search_sensor(LEGO_EV3_GYRO, &gyro_sensor_id, 0) )
  {
    sprintf(msg, " --> No LEGO_EV3_GYRO found\n\tAborting...\n");
    log_to_file(msg);
    return 0;
  }
  
  get_sensor_value(0, gyro_sensor_id, &initial_absolute_angle);
  sprintf(msg, "[GYRO] : Initial absolute value %d\n", initial_absolute_angle);
  log_to_file(msg);
  
  set_tacho_command_inx(engine1, TACHO_RESET );
  set_tacho_command_inx(engine2, TACHO_RESET );
  
  get_tacho_max_speed(engine1, &max_speed);
  set_tacho_speed_sp(engine1, max_speed / 20);
  set_tacho_speed_sp(engine2, max_speed / 20);
  set_tacho_ramp_up_sp(engine1, 0);
  set_tacho_ramp_down_sp(engine1, 0);
  set_tacho_position_sp(engine1, 180);
  //msleep(1000);
  set_tacho_command_inx(engine1, TACHO_RUN_TO_REL_POS );
  set_tacho_command_inx(engine2, TACHO_STOP);
  
  msleep(5000);
  
  get_sensor_value(0, gyro_sensor_id, &final_absolute_angle);
  sprintf(msg, "[GYRO] : Final absolute value %d\n", final_absolute_angle);
  log_to_file(msg);
  
  set_tacho_position_sp(engine1, -180);
  set_tacho_command_inx(engine1, TACHO_RUN_TO_REL_POS);
  
  msleep(5000);
  get_sensor_value(0, gyro_sensor_id, &initial_absolute_angle);
  sprintf(msg, "[GYRO] : Restart absolute value %d\n", initial_absolute_angle);
  log_to_file(msg);
  
  
  if ((final_absolute_angle - initial_absolute_angle) < 0)
  {
    engines[R].address = engine1;
    engines[L].address = engine2;
  }
  else
  {
    engines[R].address = engine2;
    engines[L].address = engine1;
  }
  engines[R].dirty = 0;
  engines[L].dirty = 0;
  
  set_tacho_command_inx(engine1, TACHO_RESET);
  set_tacho_command_inx(engine2, TACHO_RESET);
  
  pthread_create(&engine_manager_tid, NULL, tacho_manager, (void*)engines);
  
  return 1;
}



void robot_deinit()
{
  pthread_cancel(engine_manager_tid);
}
