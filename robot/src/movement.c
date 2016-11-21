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

inline void
turn_engine_by_angle(int16_t angle, engine_ptr engine, uint8_t speed_mod)
{
  int max_speed;
  int count_per_rot;
  int count_to_rotate;
  
  FLAGS_T status;

  get_tacho_max_speed(engine, &max_speed);
    
  get_tacho_count_per_rot(engine, &count_per_rot);
    
  set_tacho_speed_sp(engine, max_speed / speed_mod);
    
  set_tacho_ramp_up_sp(engine, 5000);
    
  set_tacho_ramp_down_sp(engine, 3500);
    
  count_to_rotate = (int)((angle) * 2 * count_per_rot / 360);
  set_tacho_position_sp(engine, count_to_rotate);
  
  set_tacho_command_inx(engine, TACHO_RUN_TO_REL_POS);
    
  //  sprintf(msg, "Turn Engine #%d --> %d deg @ speed %d\n",
  //         engine, angle, (int)(max_speed / speed_mod));
  //log_to_file(msg);
    
  do {
    msleep(100);
    //printf("STATUS: ");
    get_tacho_state_flags(engine, &status);
    //printf("%d\n", status);
    
    //char status_c[100];
    //get_tacho_state(engine, status_c, 100);
    //printf("%s\n", status_c);
    
  } while ((status % 2) == 1);

  set_tacho_stop_action_inx(engine, TACHO_HOLD);
  set_tacho_command_inx(engine, TACHO_STOP);
  
}


inline void
turn_engine_by_time(uint16_t time, engine_ptr engine, uint8_t speed)
{

  FLAGS_T status;
  
  set_tacho_stop_action_inx(engine, TACHO_COAST);
  
  set_tacho_time_sp(engine, time);
  
  set_tacho_speed_sp(engine, speed);
  
  set_tacho_ramp_up_sp(engine, 0);
  
  set_tacho_ramp_down_sp(engine, 0);
  
  set_tacho_command_inx(engine, TACHO_RUN_TIMED);

  //  sprintf(msg, "Turn Engine #%d --> %d deg @ speed %d\n",
  //         engine, angle, (int)(max_speed / speed_mod));
  //log_to_file(msg);
  
  //set_tacho_command_inx(engine, TACHO_HOLD);
  
  do {
    msleep(100);
    //printf("STATUS: ");
    get_tacho_state_flags(engine, &status);
    //printf("%d\n", status);
  } while (!(status == 2 || status == 0));
}

void*
thread_turn_engine_by_angle(void *arg)
{
  turn_engine_arg_struct valid_args = *(turn_engine_arg_struct*)arg;
  
  sem_wait(&valid_args.sem_engine);
  turn_engine_by_angle(valid_args.angle, valid_args.engine, valid_args.speed_mod);
  sem_post(&valid_args.sem_engine);
  
  pthread_exit(NULL);
}

void*
thread_turn_engine_by_time(void *arg)
{
  turn_engine_arg_struct valid_args = *(turn_engine_arg_struct*)arg;
  
  sem_wait(&valid_args.sem_engine);
  turn_engine_by_time(valid_args.time, valid_args.engine, valid_args.speed_mod);
  sem_post(&valid_args.sem_engine);
  
  pthread_exit(NULL);
}

void
turn_inplace_by_relative_angle(int16_t angle, engine_ptr right_engine, engine_ptr left_engine)
{
  turn_engine_arg_struct right_engine_args, left_engine_args;
  pthread_t right_tid, left_tid;
  
  int initial_orientation, final_orientation;
  sensor_ptr gyro_sensor_id;
  int16_t error = angle;
  
  // Search the gyroscope
  if( !ev3_search_sensor(LEGO_EV3_GYRO, &gyro_sensor_id, 0) )
  {
    sprintf(msg, " --> No LEGO_EV3_GYRO found\n\tAborting...\n");
    log_to_file(msg);
    return;
  }
  set_sensor_poll_ms(gyro_sensor_id, 10);
  set_sensor_mode(gyro_sensor_id, "GYRO-ANG");
  get_sensor_value(0, gyro_sensor_id, &initial_orientation);

  int i = 0;
  
  sprintf(msg, "Turn %s %+d\n", (angle > 0 ? "right" : "left") , angle);
  log_to_file(msg);
  
  do {
  
    right_engine_args.angle = -error;
    right_engine_args.engine = right_engine;
    right_engine_args.speed_mod = 2;
    right_engine_args.sem_engine = sem_right_engine;
    
    left_engine_args.angle = +error;
    left_engine_args.engine = left_engine;
    left_engine_args.speed_mod = 2;
    left_engine_args.sem_engine = sem_left_engine;
  
    pthread_create(&right_tid, NULL, thread_turn_engine_by_angle, (void*)&right_engine_args);
    pthread_create(&left_tid,  NULL, thread_turn_engine_by_angle, (void*)&left_engine_args);
  
    pthread_join(left_tid, NULL);
    pthread_join(right_tid, NULL);

    get_sensor_value(0, gyro_sensor_id, &final_orientation);
    error = -(final_orientation - initial_orientation) + angle;

    sprintf(msg, "\t Iter #%d -- Initial: %d\tTarget: %d\tActual: %d\tError: %d\n",
            i, initial_orientation, angle, final_orientation, error);
    log_to_file(msg);
    i++;
} while (abs(error) > 0);
  
  return;
}


void
go_straight(uint16_t time, uint16_t speed, engine_ptr right_engine, engine_ptr left_engine)
{
  //turn_engine_arg_struct right_engine_args, left_engine_args;
  //pthread_t right_tid, left_tid, error_tid;
  //struct timeval start_time, current_time, diff_time;
  //uint16_t remaining_time;
  int previous_error, current_error;
  int initial_orientation,current_orientation;
  sensor_ptr compass_sensor_id;
  
  // Search the gyroscope
  if( !ev3_search_sensor(LEGO_EV3_GYRO, &compass_sensor_id, 0) )
  {
    sprintf(msg, " --> No HT_NXT_COMPASS found\n\tAborting...\n");
    log_to_file(msg);
    return;
  }
  set_sensor_poll_ms(compass_sensor_id, 10);

  
  set_tacho_stop_action_inx(right_engine, TACHO_COAST);
  set_tacho_stop_action_inx(left_engine, TACHO_COAST);
  
  set_tacho_speed_sp(right_engine, speed);
  set_tacho_speed_sp(left_engine, speed);
  
  set_tacho_ramp_up_sp(right_engine, 0);
  set_tacho_ramp_up_sp(left_engine, 0);
  
  set_tacho_ramp_down_sp(right_engine, 0);
  set_tacho_ramp_down_sp(left_engine, 0);

  set_tacho_time_sp(right_engine, time);
  set_tacho_time_sp(left_engine, time);
  
  set_tacho_command_inx(right_engine, TACHO_RUN_TIMED);
  set_tacho_command_inx(left_engine, TACHO_RUN_TIMED);
  
  //set_tacho_command_inx(right_engine, TACHO_STOP);
  //set_tacho_command_inx(left_engine, TACHO_STOP);
  int i;
  previous_error = 0;
  get_sensor_value(0, compass_sensor_id, &initial_orientation);
  
  for (i = 0; i < time; i += 500)
  {
    get_sensor_value(0, compass_sensor_id, &current_orientation);
    current_error = (current_orientation - initial_orientation);
    printf("Iter #%d - Initial orientation: %d - Final orientation: %d - Error: %d\n",
           i, initial_orientation, current_orientation, current_error);
    
    if (abs(current_error) > 2) {
      set_tacho_command_inx(right_engine, TACHO_STOP);
      set_tacho_command_inx(left_engine, TACHO_STOP);
      turn_inplace_by_relative_angle(-2 * current_error - 1.1 * previous_error,
                                     right_engine, left_engine);
      previous_error = current_error;
      set_tacho_time_sp(right_engine, time - i);
      set_tacho_time_sp(left_engine, time - i);
      
      set_tacho_stop_action_inx(right_engine, TACHO_COAST);
      set_tacho_stop_action_inx(left_engine, TACHO_COAST);
      
      set_tacho_speed_sp(right_engine, speed);
      set_tacho_speed_sp(left_engine, speed);
      
      set_tacho_ramp_up_sp(right_engine, 0);
      set_tacho_ramp_up_sp(left_engine, 0);
      set_tacho_ramp_down_sp(right_engine, 0);
      set_tacho_ramp_down_sp(left_engine, 0);
      set_tacho_command_inx(right_engine, TACHO_RUN_TIMED);
      set_tacho_command_inx(left_engine, TACHO_RUN_TIMED);
    }
    msleep(500);
  }
  
  
  
  
  
  
  //right_engine_args.time = time;
  //right_engine_args.engine = right_engine;
  //right_engine_args.speed_mod = speed;
  //right_engine_args.sem_engine = sem_right_engine;
  
  //left_engine_args.time = time;
  //left_engine_args.engine = left_engine;
  //left_engine_args.speed_mod = speed;
  //left_engine_args.sem_engine = sem_left_engine;
  

  //gettimeofday(&start_time, NULL);
  
  //pthread_create(&right_tid, NULL, thread_turn_engine_by_time, (void*)&right_engine_args);
  //pthread_create(&left_tid,  NULL, thread_turn_engine_by_time, (void*)&left_engine_args);
  //pthread_create(&error_tid, NULL, thread_check_azimut, NULL);

  
  //gettimeofday(&current_time, NULL);
  
  //timersub(&current_time, &start_time, &diff_time);
  
  //printf("Time elapsed: %ld.%06ld\n", (long int)diff_time.tv_sec, (long int)diff_time.tv_usec);
  //remaining_time = diff_time.tv_sec * 1000 + diff_time.tv_usec;
  
  //pthread_join(left_tid, NULL);
  //pthread_join(right_tid, NULL);
  
  

  return;
}

void *thread_check_azimut() {
  int initial_orientation,final_orientation;
  sensor_ptr compass_sensor_id;
  
  // Search the gyroscope
  if( !ev3_search_sensor(HT_NXT_COMPASS, &compass_sensor_id, 0) )
  {
    sprintf(msg, " --> No HT_NXT_COMPASS found\n\tAborting...\n");
    log_to_file(msg);
    pthread_exit(NULL);
  }
  set_sensor_poll_ms(compass_sensor_id, 10);
  get_sensor_value(0, compass_sensor_id, &initial_orientation);
  FLAG_adjust = 0;

  while (1) {
    msleep(100);
    get_sensor_value(0, compass_sensor_id, &final_orientation);
    int error = (final_orientation - initial_orientation);
    
    if ( abs(error) > AZIMUT_ERROR) {
      FLAG_adjust = error;
    }
  }
  
  //pthread_exit(NULL);

}
