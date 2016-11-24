//
//  tacho.c
//  robot
//
//  Created by Simone Rossi on 21/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "tacho.h"

inline int   read_count_per_rot     (engine* tacho)
{
  int tmp;
  get_tacho_count_per_rot(tacho->address, &tmp);
  return tmp;
}

inline int   read_count_per_m       (engine* tacho)
{
  int tmp;
  get_tacho_count_per_m(tacho->address, &tmp);
  return tmp;
}

inline int   read_full_travel_count (engine* tacho)
{
  int tmp;
  get_tacho_full_travel_count(tacho->address, &tmp);
  return tmp;
}

inline int   read_duty_cycle        (engine* tacho)
{
  int tmp;
  get_tacho_duty_cycle(tacho->address, &tmp);
  return tmp;
}

inline int   read_duty_cycle_sp     (engine* tacho)
{
  int tmp;
  get_tacho_duty_cycle_sp(tacho->address, &tmp);
  return tmp;
}

inline int   read_position          (engine* tacho)
{
  int tmp;
  get_tacho_position(tacho->address, &tmp);
  return tmp;
}

inline int   read_hold_pid_Kd       (engine* tacho)
{
  int tmp;
  get_tacho_hold_pid_Kd(tacho->address, &tmp);
  return tmp;
}

inline int   read_hold_pid_Ki       (engine* tacho)
{
  int tmp;
  get_tacho_hold_pid_Ki(tacho->address, &tmp);
  return tmp;
}

inline int   read_hold_pid_Kp       (engine* tacho)
{
  int tmp;
  get_tacho_hold_pid_Kp(tacho->address, &tmp);
  return tmp;
}

inline int   read_max_speed         (engine* tacho)
{
  int tmp;
  get_tacho_max_speed(tacho->address, &tmp);
  return tmp;
}

inline int   read_position_sp       (engine* tacho)
{
  int tmp;
  get_tacho_position_sp(tacho->address, &tmp);
  return tmp;
}

inline int   read_speed             (engine* tacho)
{
  int tmp;
  get_tacho_speed(tacho->address, &tmp);
  return tmp;
}

inline int   read_speed_sp          (engine* tacho)
{
  int tmp;
  get_tacho_speed_sp(tacho->address, &tmp);
  return tmp;
}

inline int   read_ramp_up_sp        (engine* tacho)
{
  int tmp;
  get_tacho_ramp_up_sp(tacho->address, &tmp);
  return tmp;
}

inline int   read_ramp_down_sp      (engine* tacho)
{
  int tmp;
  get_tacho_ramp_down_sp(tacho->address, &tmp);
  return tmp;
}

inline int   read_speed_pid_Kd      (engine* tacho)
{
  int tmp;
  get_tacho_speed_pid_Kd(tacho->address, &tmp);
  return tmp;
}

inline int   read_speed_pid_Ki      (engine* tacho)
{
  int tmp;
  get_tacho_speed_pid_Ki(tacho->address, &tmp);
  return tmp;
}

inline int   read_speed_pid_Kp      (engine* tacho)
{
  int tmp;
  get_tacho_speed_pid_Kp(tacho->address, &tmp);
  return tmp;
}

inline int   read_state             (engine* tacho)
{
  int tmp;
  get_tacho_state_flags(tacho->address, (FLAGS_T*)&tmp);
  return tmp;
}

inline int   read_stop_action       (engine* tacho)
{
  return get_tacho_stop_action_inx(tacho->address);
}

inline int   read_time_sp           (engine* tacho)
{
  int tmp;
  get_tacho_time_sp(tacho->address, &tmp);
  return tmp;
}
///**********************************************************************/


//inline void update_command           (engine* engine, int value)
//{
  //engine->command = value;
  //engine->dirty = 1;
//}

//inline void update_duty_cycle_sp     (engine* engine, int value)
//{
  //engine->duty_cycle_sp = value;
  ////engine->dirty = 1;
//}

//inline void update_polarity          (engine* engine, char* value)
//{
  //engine->polarity = value;
  ////engine->dirty = 1;
//}

//inline void update_position          (engine* engine, int value)
//{
  //engine->position = value;
  ////engine->dirty = 1;
//}

//inline void update_hold_pid_Kd       (engine* engine, int value)
//{
  //engine->hold_pid_Kd = value;
  ////engine->dirty = 1;
//}

//inline void update_hold_pid_Ki       (engine* engine, int value)
//{
  //engine->hold_pid_Ki = value;
  ////engine->dirty = 1;
//}

//inline void update_hold_pid_Kp       (engine* engine, int value)
//{
  //engine->hold_pid_Kp = value;
  ////engine->dirty = 1;
//}

//inline void update_position_sp       (engine* engine, int value)
//{
  //engine->position_sp = value;
  ////engine->dirty = 1;
//}

//inline void update_speed_sp          (engine* engine, int value)
//{
  //engine->speed_sp = value;
  ////engine->dirty = 1;
//}

//inline void update_ramp_up_sp        (engine* engine, int value)
//{
  //engine->ramp_up_sp = value;
  ////engine->dirty = 1;
//}

//inline void update_ramp_down_sp      (engine* engine, int value)
//{
  //engine->ramp_down_sp = value;
  ////engine->dirty = 1;
//}

//inline void update_speed_pid_Kd      (engine* engine, int value)
//{
  //engine->speed_pid_Kd = value;
  ////engine->dirty = 1;
//}

//inline void update_speed_pid_Ki      (engine* engine, int value)
//{
  //engine->speed_pid_Ki = value;
  ////engine->dirty = 1;
//}

//inline void update_speed_pid_Kp      (engine* engine, int value)
//{
  //engine->speed_pid_Kp = value;
  ////engine->dirty = 1;
//}

//inline void update_stop_action       (engine* engine, int value)
//{
  //engine->stop_action = value;
  ////engine->dirty = 1;
//}

//inline void update_time_sp           (engine* engine, int value)
//{
  //engine->time_sp = value;
  ////engine->dirty = 1;
//}




/**********************************************************************/
inline void write_command           (engine* tacho, int value)
{
  set_tacho_command_inx(tacho->address, value);
  return;
}

inline void write_duty_cycle_sp     (engine* tacho, int value)
{
  set_tacho_duty_cycle_sp(tacho->address, value);
  return;
}

inline void write_position          (engine* tacho, int value)
{
  set_tacho_position(tacho->address, value);
  return;
}

inline void write_hold_pid_Kd       (engine* tacho, int value)
{
  set_tacho_hold_pid_Kd(tacho->address, value);
  return;
}

inline void write_hold_pid_Ki       (engine* tacho, int value)
{
  set_tacho_hold_pid_Ki(tacho->address, value);
  return;
}

inline void write_hold_pid_Kp       (engine* tacho, int value)
{
  set_tacho_hold_pid_Kp(tacho->address, value);
  return;
}

inline void write_position_sp       (engine* tacho, int value)
{
  set_tacho_position_sp(tacho->address, value);
  return;
}

inline void write_speed_sp          (engine* tacho, int value)
{
  set_tacho_speed_sp(tacho->address, value);
  return;
}

inline void write_ramp_up_sp        (engine* tacho, int value)
{
  set_tacho_ramp_up_sp(tacho->address, value);
  return;
}

inline void write_ramp_down_sp      (engine* tacho, int value)
{
  set_tacho_ramp_down_sp(tacho->address, value);
  return;
}

inline void write_speed_pid_Kd      (engine* tacho, int value)
{
  set_tacho_speed_pid_Kd(tacho->address, value);
  return;
}

inline void write_speed_pid_Ki      (engine* tacho, int value)
{
  set_tacho_speed_pid_Ki(tacho->address, value);
  return;
}

inline void write_speed_pid_Kp      (engine* tacho, int value)
{
  set_tacho_speed_pid_Kp(tacho->address, value);
  return;
}

inline void write_stop_action       (engine* tacho, int value)
{
  set_tacho_stop_action_inx(tacho->address, value);
  return;
}

inline void write_time_sp           (engine* tacho, int value)
{
  set_tacho_time_sp(tacho->address, value);
  return;
}


void read_from_tacho (engine* tacho)
{
  
  tacho->count_per_rot     =  read_count_per_rot     (tacho);
  tacho->count_per_m       =  read_count_per_m       (tacho);
  tacho->full_travel_count =  read_full_travel_count (tacho);
  tacho->duty_cycle        =  read_duty_cycle        (tacho);
  tacho->duty_cycle_sp     =  read_duty_cycle_sp     (tacho);
  tacho->position          =  read_position          (tacho);
  tacho->hold_pid_Kd       =  read_hold_pid_Kd       (tacho);
  tacho->hold_pid_Ki       =  read_hold_pid_Ki       (tacho);
  tacho->hold_pid_Kp       =  read_hold_pid_Kp       (tacho);
  tacho->max_speed         =  read_max_speed         (tacho);
  tacho->position_sp       =  read_position_sp       (tacho);
  tacho->speed             =  read_speed             (tacho);
  tacho->speed_sp          =  read_speed_sp          (tacho);
  tacho->ramp_up_sp        =  read_ramp_up_sp        (tacho);
  tacho->ramp_down_sp      =  read_ramp_down_sp      (tacho);
  tacho->speed_pid_Kd      =  read_speed_pid_Kd      (tacho);
  tacho->speed_pid_Ki      =  read_speed_pid_Ki      (tacho);
  tacho->speed_pid_Kp      =  read_speed_pid_Kp      (tacho);
  tacho->state             =  read_state             (tacho);
  tacho->stop_action       =  read_stop_action       (tacho);
  tacho->time_sp           =  read_time_sp           (tacho);

  tacho->dirty = 0;
}
//void* __read_from_tacho (void*arg)
//{
  //read_from_tacho((engine*)arg);
  //pthread_exit(NULL);
//}


void* __tacho_status_reader (void* engines) {
    log_to_file("TACHO STATUS READER -> THREAD -- Created\n");
  while (1) {
    read_from_tacho(&((engine*)engines)[L]);
    read_from_tacho(&((engine*)engines)[R]);

    msleep(10);
  }
}
