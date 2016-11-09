//
//  movement.c
//  robot
//
//

#include "movement.h"



int
identify_engines(engine_ptr *right_engine, engine_ptr *left_engine)
{
  int max_speed = 0;
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
  if (! ev3_search_tacho(LEGO_EV3_L_MOTOR, &engine2, engine1+1) )
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
  set_tacho_speed_sp(engine1, max_speed / 16);
  set_tacho_speed_sp(engine2, max_speed / 16);
  set_tacho_ramp_up_sp(engine1, 0);
  set_tacho_ramp_down_sp(engine1, 0);
  set_tacho_position_sp(engine1, 180);
  msleep(1000);
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
    *right_engine = engine1;
    *left_engine = engine2;
  }
  else
  {
    *right_engine = engine2;
    *left_engine = engine1;
  }
  
  return 1;
  
}

void
turn_engine(int16_t angle, engine_ptr engine, uint8_t speed_mod)
{
  int max_speed;
  int count_per_rot;
  int initial_count;
  int count_to_rotate;
  int current_count;
  
  FLAGS_T status;
  int speed;
  
  get_tacho_position(engine, &initial_count);
  
  get_tacho_max_speed(engine, &max_speed);
  
  get_tacho_count_per_rot(engine, &count_per_rot);
  
  set_tacho_speed_sp(engine, max_speed / speed_mod);

  set_tacho_ramp_up_sp(engine, 1500);
  
  set_tacho_ramp_down_sp(engine, 3500);

  count_to_rotate = (int)(angle * 2 * count_per_rot / 360);
  set_tacho_position_sp(engine, count_to_rotate);

  set_tacho_command_inx(engine, TACHO_RUN_TO_REL_POS);

  sprintf(msg, "Turn engine: Engine #%d --> %d deg @ speed %d\n",
          engine, angle, (int)(max_speed / speed_mod));
  log_to_file(msg);
  
  do {
    msleep(500);
    get_tacho_state_flags(engine, &status);
    get_tacho_speed_sp(engine, &speed);
    printf("STATUS: ");
    printf("%d\n", status);
    printf("SPEED: ");
    printf("%d\n", speed);
    
  } while (!(status == 0 && speed == 0));
  
  

}

void*
thread_turn_engine(void *arg)
{
  turn_engine_arg_struct valid_args = *(turn_engine_arg_struct*)arg;
  
  sem_wait(&valid_args.sem_engine);
  turn_engine(valid_args.angle, valid_args.engine, valid_args.speed_mod);
  sem_post(&valid_args.sem_engine);
  
  pthread_exit(NULL);
}

void
turn_inplace_by_relative_angle(int16_t angle, engine_ptr right_engine, engine_ptr left_engine)
{
  turn_engine_arg_struct right_engine_args, left_engine_args;
  pthread_t right_tid, left_tid;
  
  
  right_engine_args.angle = angle;
  right_engine_args.engine = right_engine;
  right_engine_args.speed_mod = 2;
  right_engine_args.sem_engine = sem_right_engine;
  
  left_engine_args.angle = -angle;
  left_engine_args.engine = left_engine;
  left_engine_args.speed_mod = 2;
  left_engine_args.sem_engine = sem_left_engine;
  
  pthread_create(&right_tid, NULL, thread_turn_engine, (void*)&right_engine_args);
  pthread_create(&left_tid,  NULL, thread_turn_engine, (void*)&left_engine_args);
  
  pthread_join(left_tid, NULL);
  pthread_join(right_tid, NULL);
  
  return;
}
