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
  
  if (!identify_engines(&right_engine, &left_engine)) return 1;

  char status[100];
  get_tacho_state(right_engine, status, 100);
  printf("%s\n", status);
  printf("%d, %d, %d, %d, %d\n", TACHO_RUNNING, TACHO_RAMPING, TACHO_HOLDING, TACHO_OVERLOADED, TACHO_STALLED);
  
  
  test_turn_inplace_by_relative_angle();
  
  
  int time = 5000;
  
  go_straight(time, 500, right_engine, left_engine);
  
 
  
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
