#include <unistd.h>
#include <stdio.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#include "utilities.h"
#include "init.h"
#include "movement.h"

extern char msg[255];
extern sem_t sem_right_engine, sem_left_engine;

int main( void )
{
  engine_ptr right_engine, left_engine;
  
  if (!robot_init()) return 1;
  
  identify_engines(&right_engine, &left_engine);
  int i = 0;
  for (i = 0; i < 8 ; i++)
  {
    turn_inplace_by_relative_angle(45, right_engine, left_engine);
    turn_inplace_by_relative_angle(-45, right_engine, left_engine);
    sleep(1);
  }
  for (i = 0; i < 4 ; i++)
  {
    turn_inplace_by_relative_angle(90, right_engine, left_engine);
    turn_inplace_by_relative_angle(-90, right_engine, left_engine);
    sleep(1);
  }
  for (i = 0; i < 2 ; i++)
  {
    turn_inplace_by_relative_angle(180, right_engine, left_engine);
    turn_inplace_by_relative_angle(-180, right_engine, left_engine);
    sleep(1);
  }
  turn_inplace_by_relative_angle(360, right_engine, left_engine);
  turn_inplace_by_relative_angle(-360, right_engine, left_engine);

  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
