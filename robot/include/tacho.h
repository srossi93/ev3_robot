//
//  tacho.h robot
//
//  Created by Simone Rossi on 21/11/16.  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef __tacho_h
#define __tacho_h

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
#include "utilities.h"



typedef uint8_t engine_ptr;

enum {L, R, ARM};

struct foo {
  
  engine_ptr address;
  
  /** (write-only) Sends a command to the motor controller.  */
  int command;

  /** (read-only) Returns the number of tacho counts in one rotation of the motor.  Tacho counts are
   * used by the position and speed attributes, so you can use this value to convert from rotations
   * or degrees to tacho counts. */
  int count_per_rot;

  /** (read-only) Returns the number of tacho counts in one meter of travel of the motor. Tacho
   * counts are used by the position and speed attributes, so you can use this value to convert from
   * distance to tacho counts.  */
  int count_per_m;

  /** (read-only) Returns the number of tacho counts in the full travel of the motor.  When combined
   * with the count_per_m atribute, you can use this value to calculate the maximum travel distance
   * of the motor.  */
  int full_travel_count;

  /** (read-only) Returns the current duty cycle of the motor. Units are percent.  Values are -100
   * to 100.  */
  int duty_cycle;

  /** (read/write) Writing sets the duty cycle setpoint. Reading returns the current value. Units
   * are in percent. Valid values are -100 to 100. A negative value causes the motor to rotate in
   * reverse. */
  int duty_cycle_sp;

  /** (read/write) Sets the polarity of the motor. Valid values are: normal: A positive duty cycle
   * will cause the motor to rotate clockwise.  inversed: A positive duty cycle will cause the motor
   * to rotate counter-clockwise. */
  char *polarity;

  /** (read/write) Returns the current position of the motor in pulses of the rotary encoder. When
   * the motor rotates clockwise, the position will increase. Likewise, rotating counter-clockwise
   * causes the position to decrease. Writing will set the position to that value. The range is
   * -2,147,483,648 and +2,147,483,647 tachometer counts (32-bit signed integer).*/
  int position;

  /** (read/write) The derivative constant for the position PID. */
  int hold_pid_Kd;

  /** (read/write) The integral constant for the position PID. */
  int  hold_pid_Ki;

  /** (read/write) The proportional constant for the position PID. */
  int  hold_pid_Kp;

  /** (read) Returns the maximum value that is accepted by the speed_sp attribute. This may be
   * slightly different than the maximum speed that a particular motor can reach - it’s the maximum
   * theoretical speed.*/
  int  max_speed;

  /** (read/write) Writing specifies the target position for the run-to-abs-pos and run-to-rel-pos
   * commands. Reading returns the current value. Units are in tacho counts. You can use the value
   * returned by counts_per_rot to convert tacho counts to/from rotations or degrees. The range is
   * -2,147,483,648 and +2,147,483,647 tachometer counts (32-bit signed integer).*/
  int  position_sp;

  /** (read-only) Returns the current motor speed in tacho counts per second. Note, this is not
   * necessarily degrees (although it is for LEGO motors). Use the count_per_rot attribute to
   * convert this value to RPM or deg/sec. */
  int  speed;

  /** (read/write) Writing sets the target speed in tacho counts per second used for all run-*
   * commands except run-direct. Reading returns the current value. A negative value causes the
   * motor to rotate in reverse with the exception of run-to-*-pos commands where the sign is
   * ignored. Use the count_per_rot attribute to convert RPM or deg/sec to tacho counts per second.
   * Use the count_per_m attribute to convert m/s to tacho counts per second.*/
  int  speed_sp;

  /** (read/write) Writing sets the ramp up setpoint. Reading returns the current value. Units are
   * in milliseconds and must be positive. When set to a non-zero value, the motor speed will
   * increase from 0 to 100% of max_speed over the span of this setpoint. The actual ramp time is
   * the ratio of the difference between the speed_sp and the current speed and max_speed multiplied
   * by ramp_up_sp. Values must not be negative.*/
  int  ramp_up_sp;

  /** (read/write) Writing sets the ramp down setpoint. Reading returns the current value. Units are
   * in milliseconds and must be positive. When set to a non-zero value, the motor speed will
   * decrease from 0 to 100% of max_speed over the span of this setpoint. The actual ramp time is
   * the ratio of the difference between the speed_sp and the current speed and max_speed multiplied
   * by ramp_down_sp. Values must not be negative. 
  */
  int  ramp_down_sp;

  /** (read/write) The derivative constant for the speed regulation PID. */
  int  speed_pid_Kd;

  /** (read/write) The integral constant for the speed regulation PID. */
  int  speed_pid_Ki;

  /** (read/write) The proportional constant for the speed regulation PID. */
  int  speed_pid_Kp;
  
  /** (read-only) Reading returns a space separated list of state flags.*/
  int state;

  /** (read/write) Reading returns the current stop action. Writing sets the stop action. The value
   * determines the motors behavior when command is set to stop.*/
  int stop_action;

  /** (read/write) Writing specifies the amount of time the motor will run when using the run-timed
   * command. Reading returns the current value. Units are in milliseconds. Values must not be
   * negative.*/
  int time_sp;

  
  
  int dirty;
};
typedef struct foo engine;

inline int   read_count_per_rot     (engine_ptr tacho);
inline int   read_count_per_m       (engine_ptr tacho);
inline int   read_full_travel_count (engine_ptr tacho);
inline int   read_duty_cycle        (engine_ptr tacho);
inline int   read_duty_cycle_sp     (engine_ptr tacho);
inline char* read_polarity          (engine_ptr tacho);
inline int   read_position          (engine_ptr tacho);
inline int   read_hold_pid_Kd       (engine_ptr tacho);
inline int   read_hold_pid_Ki       (engine_ptr tacho);
inline int   read_hold_pid_Kp       (engine_ptr tacho);
inline int   read_max_speed         (engine_ptr tacho);
inline int   read_position_sp       (engine_ptr tacho);
inline int   read_speed             (engine_ptr tacho);
inline int   read_speed_sp          (engine_ptr tacho);
inline int   read_ramp_up_sp        (engine_ptr tacho);
inline int   read_ramp_down_sp      (engine_ptr tacho);
inline int   read_speed_pid_Kd      (engine_ptr tacho);
inline int   read_speed_pid_Ki      (engine_ptr tacho);
inline int   read_speed_pid_Kp      (engine_ptr tacho);
inline int   read_state             (engine_ptr tacho);
inline int   read_stop_action       (engine_ptr tacho);
inline int   read_time_sp           (engine_ptr tacho);




inline void update_command           (engine* engine, int value);
inline void update_duty_cycle_sp     (engine* engine, int value);
inline void update_polarity          (engine* engine, char* value);
inline void update_position          (engine* engine, int value);
inline void update_hold_pid_Kd       (engine* engine, int value);
inline void update_hold_pid_Ki       (engine* engine, int value);
inline void update_hold_pid_Kp       (engine* engine, int value);
inline void update_position_sp       (engine* engine, int value);
inline void update_speed_sp          (engine* engine, int value);
inline void update_ramp_up_sp        (engine* engine, int value);
inline void update_ramp_down_sp      (engine* engine, int value);
inline void update_speed_pid_Kd      (engine* engine, int value);
inline void update_speed_pid_Ki      (engine* engine, int value);
inline void update_speed_pid_Kp      (engine* engine, int value);
inline void update_stop_action       (engine* engine, int value);
inline void update_time_sp           (engine* engine, int value);




inline void write_command           (engine_ptr tacho, int value);
inline void write_duty_cycle_sp     (engine_ptr tacho, int value);
inline void write_polarity          (engine_ptr tacho, char* value);
inline void write_position          (engine_ptr tacho, int value);
inline void write_hold_pid_Kd       (engine_ptr tacho, int value);
inline void write_hold_pid_Ki       (engine_ptr tacho, int value);
inline void write_hold_pid_Kp       (engine_ptr tacho, int value);
inline void write_position_sp       (engine_ptr tacho, int value);
inline void write_speed_sp          (engine_ptr tacho, int value);
inline void write_ramp_up_sp        (engine_ptr tacho, int value);
inline void write_ramp_down_sp      (engine_ptr tacho, int value);
inline void write_speed_pid_Kd      (engine_ptr tacho, int value);
inline void write_speed_pid_Ki      (engine_ptr tacho, int value);
inline void write_speed_pid_Kp      (engine_ptr tacho, int value);
inline void write_stop_action       (engine_ptr tacho, int value);
inline void write_time_sp           (engine_ptr tacho, int value);

void read_from_tacho (engine* engine);
//void* __read_from_tacho (void*arg);

void write_to_tacho  (engine* engine);
//void* __write_to_tacho (void*arg);

void* __tacho_status_reader (void* engines);

#endif /* tacho_h */
