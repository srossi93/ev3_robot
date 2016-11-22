#include <unistd.h>
#include <stdio.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#include "include.h"

//extern char msg[255];
//extern sem_t sem_right_engine, sem_left_engine;

int main( void )
{
  if (!robot_init()) return 1;
  
  printf("Max speed(L): %d\n", engines[L].max_speed);

  
  robot_deinit();
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
