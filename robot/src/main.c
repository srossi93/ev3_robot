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
#include "tacho.h"
#include "movement.h"
#include "init.h"
#include "test.h"


int main( void )
{
  if (!robot_init()) return 1;
  
  msleep(1000);
  printf("Address(L): %d\n", engines[L].address);
  printf("Address(R): %d\n", engines[R].address);
  
  
  turn_engine_by_angle(&(engines[R]), 90, 500);
  msleep(1000);
  turn_engine_by_angle(&(engines[R]), -90, 500);
  
  msleep(5000);
  
  robot_deinit();
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
