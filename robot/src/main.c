#include <unistd.h>
#include <stdio.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#include "include.h"



int main( void )
{
  if (!robot_init()) return 1;
  
  msleep(1000);
  printf("Max speed(L): %d\n", engines[L].max_speed);
  printf("Max speed(R): %d\n", engines[R].max_speed);
  
  update_time_sp(&engines[L], 1000);
  update_speed_sp(&engines[L], 500);
  update_command(&engines[L], TACHO_RUN_TIMED);
  
  msleep(5000);
  
  robot_deinit();
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
