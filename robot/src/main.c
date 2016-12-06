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
  
  //test_square();
  
  //threads_deinit();
  
  
  //if ( !ev3_search_tacho(LEGO_EV3_L_MOTOR, &(engines[ARM].address), (engines[L].address>engines[R].address ? engines[L].address : engines[R].address) ))
  //{
    //sprintf(msg, " --> No second LEGO_EV3_L_MOTOR found\n\tAborting...\n");
    //log_to_file(msg);
    //return 0;
  //}
  
  int i;
  char s[255];
  printf( "Found tacho motors:\n" );
  for ( i = 0; i < DESC_LIMIT; i++ ) {
    if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
      printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
      printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
    }
  }
  
  //ev3_search_tacho_plugged_in(68, 0, &(engines[ARM].address), 0);
  
  printf("UP and CLOSED");
  turn_engine_by_angle(&(engines[ARM]), -250, 200);
  printf("DOWN and CLOSED");
  
  msleep(1000);
  
  turn_engine_by_angle(&(engines[ARM]), -250, 50);
  printf("DOWN and OPEN");
  
  msleep(1000);
  
  turn_engine_by_angle(&(engines[ARM]), +250, 50);
  printf("DOWN and CLOSED");
  
  msleep(1000);
  
  turn_engine_by_angle(&(engines[ARM]), +250, 200);
  printf("UP and CLOSED");

  
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
