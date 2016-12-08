#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <string.h>

#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"

#include "utilities.h"
#include "tacho.h"
#include "movement.h"
#include "init.h"
#include "test.h"
#include "grabber.h"


int main( void )
{
  if (!robot_init()) return 1;
  
   sleep(2);
  
  
  pthread_t tid = ___go_straight(1000, 200);
  
  grab_ball(&engines[ARM]);
  
  release_ball(&engines[ARM]);
  
  pthread_join(tid, NULL);
  
  threads_deinit();
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}


