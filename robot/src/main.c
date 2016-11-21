#include <unistd.h>
#include <stdio.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#include "utilities.h"
#include "init.h"
#include "movement.h"
#include "test.h"

extern char msg[255];
extern sem_t sem_right_engine, sem_left_engine;

int main( void )
{
  engine_ptr right_engine, left_engine;
  
  if (!robot_init()) return 1;
  
  //if (!identify_engines(&right_engine, &left_engine)) return 1;
  
  test_turn_inplace_by_relative_angle();
  
  //  go_straight(5000,right_engine, left_engine);
 
  //int time = 5000;
  
  //test_turn_inplace_by_relative_angle();
  //go_straight(time, 500, right_engine, left_engine);
  
  /*set_tacho_stop_action_inx(right_engine, TACHO_COAST);
  set_tacho_stop_action_inx(left_engine, TACHO_COAST);
  
  get_tacho_max_speed(right_engine, &max_speed);
  
  set_tacho_ramp_up_sp(right_engine, 0);
  set_tacho_ramp_up_sp(left_engine, 0);
  
  set_tacho_ramp_down_sp(right_engine, 0);
  set_tacho_ramp_down_sp(left_engine, 0);
  
  int i = 0;
  for (i = 0; i < max_speed; i+=100) {
    
    set_tacho_time_sp(right_engine, time);
    set_tacho_time_sp(left_engine, time);
    
    set_tacho_speed_sp(right_engine, 400);
    set_tacho_speed_sp(left_engine,  400);
    
    set_tacho_command_inx(right_engine, TACHO_RUN_TIMED);
    set_tacho_command_inx(left_engine, TACHO_RUN_TIMED);
     msleep(1000);
    set_tacho_command_inx(right_engine, TACHO_STOP);
    set_tacho_command_inx(left_engine, TACHO_STOP);
    printf("%d\n", i);
   
    
  }
  */
 /*
  msleep(3000);
  set_tacho_stop_action_inx(right_engine, TACHO_COAST);
  set_tacho_stop_action_inx(right_engine, TACHO_COAST);

  set_tacho_command_inx(right_engine, TACHO_STOP);
  set_tacho_command_inx(left_engine, TACHO_STOP);
  
  set_tacho_speed_sp(right_engine, max_speed);
  set_tacho_speed_sp(left_engine, max_speed);
  
  set_tacho_command_inx(right_engine, TACHO_RUN_TIMED);
  set_tacho_command_inx(left_engine, TACHO_RUN_TIMED);
  */
  
  
  
  //engine_ptr arm;
  
  //// Search the first engine
  //if ( !ev3_search_tacho(LEGO_EV3_L_MOTOR, &arm, 2) )
  //{
    //sprintf(msg, " --> No LEGO_EV3_L_MOTOR found\n\tAborting...\n");
    //log_to_file(msg);
    //return 0;
  //}
  
  //set_tacho_stop_action_inx(arm, TACHO_HOLD);
  //turn_engine_by_angle(30, arm, 10);
  //set_tacho_command_inx(arm, TACHO_STOP);
  
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
