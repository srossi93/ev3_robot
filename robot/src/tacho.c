//
//  tacho.c
//  robot
//
//  Created by Simone Rossi on 21/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include "tacho.h"

inline int   read_count_per_rot     (engine_ptr tacho)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return tmp;
}

inline int   read_count_per_m       (engine_ptr tacho)
{
  int tmp;
  get_tacho_count_per_m(tacho, &tmp);
  return tmp;
}

inline int   read_full_travel_count (engine_ptr tacho)
{
  int tmp;
  get_tacho_full_travel_count(tacho, &tmp);
  return tmp;
}

inline int   read_duty_cycle        (engine_ptr tacho)
{
  int tmp;
  get_tacho_duty_cycle(tacho, &tmp);
  return tmp;
}

inline int   read_duty_cycle_sp     (engine_ptr tacho)
{
  int tmp;
  get_tacho_duty_cycle_sp(tacho, &tmp);
  return tmp;
}

inline char* read_polarity          (engine_ptr tacho)
{
  char *tmp;
  get_tacho_polarity(tacho, tmp, 20);
  return tmp;
}

inline int   read_position          (engine_ptr tacho)
{
  int tmp;
  get_tacho_position(tacho, &tmp);
  return tmp;
}

inline int   read_hold_pid_Kd       (engine_ptr tacho)
{
  int tmp;
  get_tacho_hold_pid_Kd(tacho, &tmp);
  return tmp;
}

inline int   read_hold_pid_Ki       (engine_ptr tacho)
{
  int tmp;
  get_tacho_hold_pid_Ki(tacho, &tmp);
  return tmp;
}

inline int   read_hold_pid_Kp       (engine_ptr tacho)
{
  int tmp;
  get_tacho_hold_pid_Kp(tacho, &tmp);
  return tmp;
}

inline int   read_max_speed         (engine_ptr tacho)
{
  int tmp;
  get_tacho_max_speed(tacho, &tmp);
  return tmp;
}

inline int   read_position_sp       (engine_ptr tacho)
{
  int tmp;
  get_tacho_position_sp(tacho, &tmp);
  return tmp;
}

inline int   read_speed             (engine_ptr tacho)
{
  int tmp;
  get_tacho_speed(tacho, &tmp);
  return tmp;
}

inline int   read_speed_sp          (engine_ptr tacho)
{
  int tmp;
  get_tacho_speed_sp(tacho, &tmp);
  return tmp;
}

inline int   read_ramp_up_sp        (engine_ptr tacho)
{
  int tmp;
  get_tacho_ramp_up_sp(tacho, &tmp);
  return tmp;
}

inline int   read_ramp_down_sp      (engine_ptr tacho)
{
  int tmp;
  get_tacho_ramp_down_sp(tacho, &tmp);
  return tmp;
}

inline int   read_speed_pid_Kd      (engine_ptr tacho)
{
  int tmp;
  get_tacho_speed_pid_Kd(tacho, &tmp);
  return tmp;
}

inline int   read_speed_pid_Ki      (engine_ptr tacho)
{
  int tmp;
  get_tacho_speed_pid_Ki(tacho, &tmp);
  return tmp;
}

inline int   read_speed_pid_Kp      (engine_ptr tacho)
{
  int tmp;
  get_tacho_speed_pid_Kp(tacho, &tmp);
  return tmp;
}

inline int   read_state             (engine_ptr tacho)
{
  int tmp;
  get_tacho_state_flags(tacho, &tmp);
  return tmp;
}

inline int   read_stop_action       (engine_ptr tacho)
{
  return get_tacho_stop_action_inx(tacho);
}

inline int   read_time_sp           (engine_ptr tacho)
{
  int tmp;
  get_tacho_time_sp(tacho, &tmp);
  return tmp;
}
/**********************************************************************/


inline void update_command           (engine* engine, int value)
{
  engine->command = value;
  engine->dirty = 1;
}

inline void update_duty_cycle_sp     (engine* engine, int value)
{
  engine->duty_cycle_sp = value;
  engine->dirty = 1;
}

inline void update_polarity          (engine* engine, char* value)
{
  engine->polarity = value;
  engine->dirty = 1;
}

inline void update_position          (engine* engine, int value)
{
  engine->position = value;
  engine->dirty = 1;
}

inline void update_hold_pid_Kd       (engine* engine, int value)
{
  engine->hold_pid_Kd = value;
  engine->dirty = 1;
}

inline void update_hold_pid_Ki       (engine* engine, int value)
{
  engine->hold_pid_Ki = value;
  engine->dirty = 1;
}

inline void update_hold_pid_Kp       (engine* engine, int value)
{
  engine->hold_pid_Kp = value;
  engine->dirty = 1;
}

inline void update_position_sp       (engine* engine, int value)
{
  engine->position_sp = value;
  engine->dirty = 1;
}

inline void update_speed_sp          (engine* engine, int value)
{
  engine->speed_sp = value;
  engine->dirty = 1;
}

inline void update_ramp_up_sp        (engine* engine, int value)
{
  engine->ramp_up_sp = value;
  engine->dirty = 1;
}

inline void update_ramp_down_sp      (engine* engine, int value)
{
  engine->ramp_down_sp = value;
  engine->dirty = 1;
}

inline void update_speed_pid_Kd      (engine* engine, int value)
{
  engine->speed_pid_Kd = value;
  engine->dirty = 1;
}

inline void update_speed_pid_Ki      (engine* engine, int value)
{
  engine->speed_pid_Ki = value;
  engine->dirty = 1;
}

inline void update_speed_pid_Kp      (engine* engine, int value)
{
  engine->speed_pid_Kp = value;
  engine->dirty = 1;
}

inline void update_stop_action       (engine* engine, int value)
{
  engine->stop_action = value;
  engine->dirty = 1;
}

inline void update_time_sp           (engine* engine, int value)
{
  engine->time_sp = value;
  engine->dirty = 1;
}




/**********************************************************************/
inline void write_command           (engine_ptr tacho, int value)
{
  set_tacho_command_inx(tacho, value);
  return;
}

inline void write_duty_cycle_sp     (engine_ptr tacho, int value)
{
  set_tacho_duty_cycle_sp(tacho, value);
  return;
}

inline void write_polarity          (engine_ptr tacho, char* value)
{
  set_tacho_polarity(tacho, value);
  return;
}

inline void write_position          (engine_ptr tacho, int value)
{
  set_tacho_position(tacho, value);
  return;
}

inline void write_hold_pid_Kd       (engine_ptr tacho, int value)
{
  set_tacho_hold_pid_Kd(tacho, value);
  return;
}

inline void write_hold_pid_Ki       (engine_ptr tacho, int value)
{
  set_tacho_hold_pid_Ki(tacho, value);
  return;
}

inline void write_hold_pid_Kp       (engine_ptr tacho, int value)
{
  set_tacho_hold_pid_Kp(tacho, value);
  return;
}

inline void write_position_sp       (engine_ptr tacho, int value)
{
  set_tacho_position_sp(tacho, value);
  return;
}

inline void write_speed_sp          (engine_ptr tacho, int value)
{
  set_tacho_speed_sp(tacho, value);
  return;
}

inline void write_ramp_up_sp        (engine_ptr tacho, int value)
{
  set_tacho_ramp_up_sp(tacho, value);
  return;
}

inline void write_ramp_down_sp      (engine_ptr tacho, int value)
{
  set_tacho_ramp_down_sp(tacho, value);
  return;
}

inline void write_speed_pid_Kd      (engine_ptr tacho, int value)
{
  set_tacho_speed_pid_Kd(tacho, value);
  return;
}

inline void write_speed_pid_Ki      (engine_ptr tacho, int value)
{
  set_tacho_speed_pid_Ki(tacho, value);
  return;
}

inline void write_speed_pid_Kp      (engine_ptr tacho, int value)
{
  set_tacho_speed_pid_Kp(tacho, value);
  return;
}

inline void write_stop_action       (engine_ptr tacho, int value)
{
  set_tacho_stop_action_inx(tacho, value);
  return;
}

inline void write_time_sp           (engine_ptr tacho, int value)
{
  set_tacho_time_sp(tacho, value);
  return;
}


void read_from_tacho (engine* engine)
{
  engine_ptr tacho = engine->address;
  
  engine->count_per_rot     =  read_count_per_rot     (tacho);
  engine->count_per_m       =  read_count_per_m       (tacho);
  engine->full_travel_count =  read_full_travel_count (tacho);
  engine->duty_cycle        =  read_duty_cycle        (tacho);
  engine->duty_cycle_sp     =  read_duty_cycle_sp     (tacho);
  engine->polarity          =  read_polarity          (tacho);
  engine->position          =  read_position          (tacho);
  engine->hold_pid_Kd       =  read_hold_pid_Kd       (tacho);
  engine->hold_pid_Ki       =  read_hold_pid_Ki       (tacho);
  engine->hold_pid_Kp       =  read_hold_pid_Kp       (tacho);
  engine->max_speed         =  read_max_speed         (tacho);
  engine->position_sp       =  read_position_sp       (tacho);
  engine->speed             =  read_speed             (tacho);
  engine->speed_sp          =  read_speed_sp          (tacho);
  engine->ramp_up_sp        =  read_ramp_up_sp        (tacho);
  engine->ramp_down_sp      =  read_ramp_down_sp      (tacho);
  engine->speed_pid_Kd      =  read_speed_pid_Kd      (tacho);
  engine->speed_pid_Ki      =  read_speed_pid_Ki      (tacho);
  engine->speed_pid_Kp      =  read_speed_pid_Kp      (tacho);
  engine->state             =  read_state             (tacho);
  engine->stop_action       =  read_stop_action       (tacho);
  engine->time_sp           =  read_time_sp           (tacho);

  engine->dirty = 0;
}


void write_to_tacho  (engine* engine)
{
  engine_ptr tacho = engine->address;
  
  if (!engine->dirty) return;
  
  write_command      (tacho, engine->command      ); 
  write_duty_cycle_sp(tacho, engine->duty_cycle_sp); 
  write_polarity     (tacho, engine->polarity     ); 
  write_position     (tacho, engine->position     ); 
  write_hold_pid_Kd  (tacho, engine->hold_pid_Kd  ); 
  write_hold_pid_Ki  (tacho, engine->hold_pid_Ki  ); 
  write_hold_pid_Kp  (tacho, engine->hold_pid_Kp  ); 
  write_position_sp  (tacho, engine->position_sp  ); 
  write_speed_sp     (tacho, engine->speed_sp     ); 
  write_ramp_up_sp   (tacho, engine->ramp_up_sp   ); 
  write_ramp_down_sp (tacho, engine->ramp_down_sp ); 
  write_speed_pid_Kd (tacho, engine->speed_pid_Kd ); 
  write_speed_pid_Ki (tacho, engine->speed_pid_Ki ); 
  write_speed_pid_Kp (tacho, engine->speed_pid_Kp ); 
  write_stop_action  (tacho, engine->stop_action  ); 
  write_time_sp      (tacho, engine->time_sp      ); 

  engine->dirty = 0;

}
