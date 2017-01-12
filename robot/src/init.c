//
//  init.c
//  robot
//
//  Created by Simone Rossi on 08/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "init.h"
#include "globals.h"

extern char msg[255];
//extern sem_t sem_right_engine, sem_left_engine;

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

  sensor_init();
  engines_init();
  threads_init();
  
  turn_inplace_by_relative_angle(-gyro->angle, 200);
  
  sleep(2);

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
  if ( !ev3_search_tacho_plugged_in(65, 0, &engine1, 0) )
  {
    sprintf(msg, " --> No LEGO_EV3_L_MOTOR found\n\tAborting...\n");
    log_to_file(msg);
    return 0;
  }
  
  // Search the second engine
  if ( !ev3_search_tacho_plugged_in(66, 0, &engine2, 0) )
  {
    sprintf(msg, " --> No second LEGO_EV3_L_MOTOR found\n\tAborting...\n");
    log_to_file(msg);
    return 0;
  }
  
  ev3_search_tacho_plugged_in(68, 0, &(engines[ARM].address), 0);
  set_tacho_command_inx(engines[ARM].address, TACHO_RESET);
  
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
  set_tacho_position_sp(engine1, 90);
  //msleep(1000);
  set_tacho_command_inx(engine1, TACHO_RUN_TO_REL_POS );
  set_tacho_command_inx(engine2, TACHO_STOP);
  
  msleep(3000);
  
  get_sensor_value(0, gyro_sensor_id, &final_absolute_angle);
  sprintf(msg, "[GYRO] : Final absolute value %d\n", final_absolute_angle);
  log_to_file(msg);
  
  set_tacho_position_sp(engine1, -90);
  set_tacho_command_inx(engine1, TACHO_RUN_TO_REL_POS);
  
  msleep(3000);
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
  set_tacho_command_inx(engines[ARM].address, TACHO_RESET);
  
  set_tacho_command_inx(engines[L].address, TACHO_RESET );
  set_tacho_command_inx(engines[R].address, TACHO_RESET );
  set_tacho_command_inx(engines[ARM].address, TACHO_RESET );

  arm_status = ARM_UP;
  
  
  
  return 1;
}

void sensor_init(){
  
  int i;
  for ( i = 0; i < DESC_LIMIT; i++ ) {
    if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
      if ( !strcmp(ev3_sensor_type( ev3_sensor[ i ].type_inx ), "lego-ev3-color") )
        color->address=i;
      
      if ( !strcmp(ev3_sensor_type( ev3_sensor[ i ].type_inx ), "lego-ev3-gyro") )
        gyro->address=i;
      
      if ( !strcmp(ev3_sensor_type( ev3_sensor[ i ].type_inx ), "lego-ev3-us") )
        us->address=i;
      
    }
  }

  log_to_file("GYRO Calibration...\n");
  set_sensor_mode(gyro->address, "GYRO-CAL");
  msleep(1000);
  log_to_file("GYRO Calibration Done\n");
  set_sensor_mode(gyro->address, "GYRO-G&A");
  pthread_mutex_init(&gyro_mutex, NULL);
  

  set_sensor_mode(us->address, "US-DIST-CM");
  pthread_mutex_init(&us_mutex, NULL);
  
  
  set_sensor_mode(color->address, "COL-REFLECT");
  pthread_mutex_init(&color_mutex, NULL);
  
  
}

void threads_init(){
  pthread_create(&engines_status_reader_tid, NULL, __tacho_status_reader, (void*)engines);
  log_to_file("TACHO STATUS READER -> THREAD -- Created\n");
  pthread_create(&gyro_status_reader_tid, NULL, __gyro_status_reader, (void*)gyro);
  log_to_file("GYRO STATUS READER -> THREAD -- Created\n");
  pthread_create(&us_status_reader_tid, NULL, __us_status_reader, (void*)us);
  log_to_file("US STATUS READER -> THREAD -- Created\n");
  pthread_create(&color_status_reader_tid, NULL, __color_status_reader, (void*)color);
  log_to_file("COLOR STATUS READER -> THREAD -- Created\n");
}



void threads_deinit()
{
  pthread_cancel(engines_status_reader_tid);
  log_to_file("TACHO STATUS READER -> THREAD -- Terminated\n");
  pthread_cancel(gyro_status_reader_tid);
  log_to_file("GYRO STATUS READER -> THREAD -- Terminated\n");
  pthread_cancel(us_status_reader_tid);
  log_to_file("US STATUS READER -> THREAD -- Terminated\n");
}
