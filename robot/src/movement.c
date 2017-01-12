/**
//  movement.c
//  robot
//
*/

#include "movement.h"


inline void
turn_engine_by_angle(engine* tacho, int16_t angle, int16_t speed)
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
    
  } while (((tacho->state % 2) == 1));
  
  write_stop_action(tacho, TACHO_HOLD);
  write_command(tacho, TACHO_STOP);
  
}


inline void
turn_engine_by_time(engine* tacho, uint16_t time, int16_t speed)
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
turn_inplace_by_relative_angle(int16_t angle, int16_t speed)
{
  turn_engine_arg_struct right_engine_args, left_engine_args;
  pthread_t right_tid, left_tid;
  
  int initial_orientation, final_orientation;
  //sensor_ptr gyro_sensor_id;
  int16_t error = angle;
  
  // Search the gyroscope
  //if( !ev3_search_sensor(LEGO_EV3_GYRO, &gyro_sensor_id, 0) )
  //{
    //sprintf(msg, " --> No LEGO_EV3_GYRO found\n\tAborting...\n");
    //log_to_file(msg);
    //return;
  //}
  pthread_mutex_lock(&gyro_mutex);
  initial_orientation = gyro->angle;
  pthread_mutex_unlock(&gyro_mutex);
  
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

    pthread_join(right_tid, NULL);
    pthread_join(left_tid, NULL);

    
    //msleep(500);

    pthread_mutex_lock(&gyro_mutex);
    final_orientation = gyro->angle;
    pthread_mutex_unlock(&gyro_mutex);
    
    //get_sensor_value(0, gyro_sensor_id, &final_orientation);
    error = -(final_orientation - initial_orientation) + angle;

    sprintf(msg, "\t Iter #%d -- Initial: %d\tTarget: %d\tActual: %d\tError: %d\n",
            i, initial_orientation, angle, final_orientation, error);
    log_to_file(msg);
    i++;
} while (abs(error) > 1);
  
  return;
}


void
go_straight(uint16_t time, int16_t speed, FLAGS_T check_orientation)
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
  
  write_ramp_up_sp(&engines[R], 2000);
  write_ramp_up_sp(&engines[L], 2000);
  
  write_ramp_down_sp(&engines[R], 500);
  write_ramp_down_sp(&engines[L], 500);
  
  write_time_sp(&engines[R], time);
  write_time_sp(&engines[L], time);
  
  write_command(&engines[R], TACHO_RUN_TIMED);
  write_command(&engines[L], TACHO_RUN_TIMED);

  //printf("Command sent\n");
  
  if (check_orientation == 0) return;
  //set_tacho_command_inx(right_engine, TACHO_STOP);
  //set_tacho_command_inx(left_engine, TACHO_STOP);
  //printf("ERROR detection\n");
  int i;
  previous_error = 0;
  
  pthread_mutex_lock(&gyro_mutex);
  initial_orientation = gyro->angle;
  pthread_mutex_unlock(&gyro_mutex);
  
  for (i = 0; i < time-500; i += 250)
  {
    pthread_mutex_lock(&gyro_mutex);
    current_orientation = gyro->angle;
    pthread_mutex_unlock(&gyro_mutex);
    
    
    
    current_error = (current_orientation - initial_orientation);
    sprintf(msg, "Time: %d ms - Error: %d\n",
           i, current_error);
    log_to_file(msg);

    write_ramp_up_sp(&engines[R], 1000);
    write_ramp_up_sp(&engines[L], 1000);
    
    if (abs(current_error) > 4) {
      write_command(&engines[R], TACHO_STOP);
      write_command(&engines[L], TACHO_STOP);
      turn_inplace_by_relative_angle(-current_error, 200);
      previous_error = current_error;
      
      write_time_sp(&engines[R], time - i);
      write_time_sp(&engines[L], time - i);

      //write_stop_action(&engines[R], TACHO_COAST);
      //write_stop_action(&engines[L], TACHO_COAST);
      
      write_speed_sp(&engines[R], speed);
      write_speed_sp(&engines[L], speed);
      
      write_ramp_up_sp(&engines[R], 2000);
      write_ramp_up_sp(&engines[L], 2000);
      
      write_ramp_down_sp(&engines[R], 0);
      write_ramp_down_sp(&engines[L], 0);
      
      write_command(&engines[R], TACHO_RUN_TIMED);
      write_command(&engines[L], TACHO_RUN_TIMED);
    }
    msleep(250);
  }
  msleep(500);
  
  pthread_mutex_lock(&gyro_mutex);
  current_orientation = gyro->angle;
  pthread_mutex_unlock(&gyro_mutex);
  
  if (abs(current_orientation - initial_orientation) > 0) {
    pthread_mutex_lock(&gyro_mutex);
    int gyro_angle = gyro->angle;
    pthread_mutex_unlock(&gyro_mutex);
    turn_inplace_by_relative_angle(-(gyro_angle - initial_orientation), 200);
    
  }
  return;
}


void *
__go_straight(void* arg){
  
  turn_engine_arg_struct args = *(turn_engine_arg_struct*) arg;
  
  go_straight(args.time, args.speed, 1);
  
  pthread_exit(NULL);
}


pthread_t
___go_straight(uint16_t time, int16_t speed){
  pthread_t tid;
  
  turn_engine_arg_struct arg;
  arg.time = time;
  arg.speed = speed;
  
  pthread_create(&tid, NULL, __go_straight, (void*)&arg);
  return tid;
}

void 
stop_engines(void){
//function to stop all the motors at the same time
  write_stop_action(&engines[R], TACHO_BRAKE);
  write_stop_action(&engines[L], TACHO_BRAKE);
  
  write_command(&engines[R],TACHO_STOP);
	write_command(&engines[L],TACHO_STOP);

}


uint16_t
go_straight_dist(int16_t position, int16_t speed, FLAGS_T check_orientation){
  
  /** Table conversion between tacho speed and cm/second */
  /** Sampled every 100 tacho speed */
  float conversion_speed_table[] = {0, 5.8, 10.6, 15.2, 19.1, 23.5};
  uint16_t time;

  if (speed > 500)
    speed = 500;
  
  time = ((speed * 1500 / 4000)) + abs((int)(position * 1000 / conversion_speed_table[(int)speed/100])) ;

  log_to_file("Moving ahead ...");
  if (position < 0) 
    speed = -speed;
  
  go_straight(time, speed, check_orientation);
  
  if (check_orientation == 0) return time;
  return 0;
}


void *
__go_straight_dist(void* arg){
  
  turn_engine_arg_struct args = *(turn_engine_arg_struct*) arg;
  
  go_straight_dist(args.distance, args.speed, 1);
  
  pthread_exit(NULL);
}


pthread_t
___go_straight_dist(int16_t distance, int16_t speed){
  pthread_t tid;
  
  turn_engine_arg_struct arg;
  arg.distance = distance;
  arg.speed = speed;
  
  pthread_create(&tid, NULL, __go_straight_dist, (void*)&arg);
  return tid;
}



void
go_to_position(int16_t x, int16_t y, int16_t speed){
  go_straight_dist(y, speed, 1);
  
  if(x < 0)
    turn_inplace_by_relative_angle(-90, 250);
  else
    turn_inplace_by_relative_angle(90, 250);
  
  go_straight_dist(abs(x), speed, 1);
  
}