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








inline void write_command           (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_duty_cycle_sp     (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_polarity          (engine_ptr tacho, char* value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_position          (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_hold_pid_Kd       (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_hold_pid_Ki       (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_hold_pid_Kp       (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_position_sp       (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_speed_sp          (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_ramp_up_sp        (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_ramp_down_sp      (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_speed_pid_Kd      (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_speed_pid_Ki      (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_speed_pid_Kp      (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_stop_action       (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}

inline void write_time_sp           (engine_ptr tacho, int value)
{
  int tmp;
  get_tacho_count_per_rot(tacho, &tmp);
  return;
}


void read_from_tacho (engine_ptr tacho);
void write_to_tacho  (engine_ptr tacho);
