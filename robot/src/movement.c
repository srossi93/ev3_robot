//
//  movement.c
//  robot
//
//

#include "movement.h"


inline void
turn_engine_by_angle(engine* tacho, int16_t angle, uint16_t speed)
{

  int count_to_rotate;
    
  write_speed_sp(tacho, speed);
  write_ramp_up_sp(tacho, 5000);
  write_ramp_down_sp(tacho, 3500);
    
  count_to_rotate = (int)((angle) * 2 * tacho->count_per_rot / 360);
  write_position_sp(tacho, count_to_rotate);
  
  write_command(tacho, TACHO_RUN_TO_REL_POS);

  do {
    msleep(500);
    //printf("STATUS: %d\n", tacho->state);
    //fflush(stdout);
    
  } while (((tacho->state % 2) == 1) || tacho->speed != 0);
  
  write_stop_action(tacho, TACHO_BRAKE);
  write_command(tacho, TACHO_STOP);
  
}


inline void
turn_engine_by_time(engine* tacho, uint16_t time, uint8_t speed)
{
  
  write_stop_action(tacho, TACHO_COAST);
  write_time_sp(tacho, time);
  write_speed_sp(tacho, speed);
  write_ramp_up_sp(tacho, 2000);
  write_ramp_down_sp(tacho, 2000);
  write_command(tacho, TACHO_RUN_TIMED);
  
  do {
    msleep(100);
  } while (((tacho->state % 2) == 1) || tacho->speed != 0);
}

void*
__turn_engine_by_angle(void *arg)
{
  turn_engine_arg_struct valid_args = *(turn_engine_arg_struct*)arg;
  
  sem_wait(&valid_args.sem_engine);
    turn_engine_by_angle(valid_args.tacho, valid_args.angle, valid_args.speed);
  sem_post(&valid_args.sem_engine);
  
  pthread_exit(NULL);
}

void*
__turn_engine_by_time(void *arg)
{
  turn_engine_arg_struct valid_args = *(turn_engine_arg_struct*)arg;
  
  sem_wait(&valid_args.sem_engine);
    turn_engine_by_time(valid_args.tacho, valid_args.time, valid_args.speed);
  sem_post(&valid_args.sem_engine);
  
  pthread_exit(NULL);
}

void
turn_inplace_by_relative_angle(int16_t angle, uint16_t speed)
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
  initial_orientation = gyro->angle;

  int i = 0;
  
  sprintf(msg, "Turn %s %+d\n", (angle > 0 ? "right" : "left") , angle);
  log_to_file(msg);
  
  do {
  
    right_engine_args.angle = -error;
    right_engine_args.tacho = &engines[R];
    right_engine_args.speed = speed;
    right_engine_args.sem_engine = sem_right_engine;
    
    left_engine_args.angle = +error;
    left_engine_args.tacho = &engines[L];
    left_engine_args.speed = speed;
    left_engine_args.sem_engine = sem_left_engine;
  
    pthread_create(&right_tid, NULL, __turn_engine_by_angle, (void*)&right_engine_args);
    pthread_create(&left_tid,  NULL, __turn_engine_by_angle, (void*)&left_engine_args);
  
    pthread_join(left_tid, NULL);
    pthread_join(right_tid, NULL);

    final_orientation = gyro->angle;
    //get_sensor_value(0, gyro_sensor_id, &final_orientation);
    error = -(final_orientation - initial_orientation) + angle;

    sprintf(msg, "\t Iter #%d -- Initial: %d\tTarget: %d\tActual: %d\tError: %d\n",
            i, initial_orientation, angle, final_orientation, error);
    log_to_file(msg);
    i++;
} while (abs(error) > 0);
  
  return;
}


void
go_straight(uint16_t time, uint16_t speed)
{
  //turn_engine_arg_struct right_engine_args, left_engine_args;
  //pthread_t right_tid, left_tid, error_tid;
  //struct timeval start_time, current_time, diff_time;
  //uint16_t remaining_time;
  int previous_error, current_error;
  int initial_orientation,current_orientation;

  
  write_stop_action(&engines[R], TACHO_COAST);
  write_stop_action(&engines[L], TACHO_COAST);

  
  write_speed_sp(&engines[R], speed);
  write_speed_sp(&engines[L], speed);
  
  write_ramp_up_sp(&engines[R], 0);
  write_ramp_up_sp(&engines[L], 0);
  
  write_ramp_down_sp(&engines[R], 0);
  write_ramp_down_sp(&engines[L], 0);
  
  write_time_sp(&engines[R], time);
  write_time_sp(&engines[L], time);
  
  write_command(&engines[R], TACHO_RUN_TIMED);
  write_command(&engines[L], TACHO_RUN_TIMED);
  
  //set_tacho_command_inx(right_engine, TACHO_STOP);
  //set_tacho_command_inx(left_engine, TACHO_STOP);
  int i;
  previous_error = 0;
  
  initial_orientation = gyro->angle;
  
  for (i = 0; i < time; i += 500)
  {
    current_orientation = gyro->angle;
    current_error = (current_orientation - initial_orientation);
    printf("Iter #%d - Initial orientation: %d - Final orientation: %d - Error: %d\n",
           i, initial_orientation, current_orientation, current_error);
    
    if (abs(current_error) > 5) {
      write_command(&engines[R], TACHO_STOP);
      write_command(&engines[L], TACHO_STOP);
      turn_inplace_by_relative_angle(-2 * current_error - 1.1 * previous_error, 200);
      previous_error = current_error;
      
      write_time_sp(&engines[R], time - i);
      write_time_sp(&engines[L], time - i);

      write_stop_action(&engines[R], TACHO_COAST);
      write_stop_action(&engines[L], TACHO_COAST);
      
      write_speed_sp(&engines[R], speed);
      write_speed_sp(&engines[L], speed);
      
      write_ramp_up_sp(&engines[R], 0);
      write_ramp_up_sp(&engines[L], 0);
      
      write_ramp_down_sp(&engines[R], 0);
      write_ramp_down_sp(&engines[L], 0);
      
      write_command(&engines[R], TACHO_RUN_TIMED);
      write_command(&engines[L], TACHO_RUN_TIMED);
    }
    msleep(500);
  }
  
  
  turn_inplace_by_relative_angle(gyro->angle - initial_orientation, 200);
  
  
  
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

//void *thread_check_azimut() {
  //int initial_orientation,final_orientation;
  //sensor_ptr compass_sensor_id;
  
  //// Search the gyroscope
  //if( !ev3_search_sensor(HT_NXT_COMPASS, &compass_sensor_id, 0) )
  //{
    //sprintf(msg, " --> No HT_NXT_COMPASS found\n\tAborting...\n");
    //log_to_file(msg);
    //pthread_exit(NULL);
  //}
  //set_sensor_poll_ms(compass_sensor_id, 10);
  //get_sensor_value(0, compass_sensor_id, &initial_orientation);
  //FLAG_adjust = 0;

  //while (1) {
    //msleep(100);
    //get_sensor_value(0, compass_sensor_id, &final_orientation);
    //int error = (final_orientation - initial_orientation);
    
    //if ( abs(error) > AZIMUT_ERROR) {
      //FLAG_adjust = error;
    //}
  //}
  
  ////pthread_exit(NULL);

//}
