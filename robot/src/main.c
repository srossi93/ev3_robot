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
  
  //while (1)
  //{
    //msleep(1000);
    //printf("%d %d\n", gyro->angle, gyro->rot_speed);
  //}
  sleep(2);
  
  test_turn_inplace_by_relative_angle();
  test_square();
  
  threads_deinit();
  
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
