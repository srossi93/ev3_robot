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
  //engine_ptr right_engine, left_engine;
  
  if (!robot_init()) return 1;
  
  //if (!identify_engines(&right_engine, &left_engine)) return 1;
  
  test_turn_inplace_by_relative_angle();

  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
