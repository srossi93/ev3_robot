#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////

#endif



#include "utilities.h"
#include "init.h"
#include "movement.h"

extern char msg[255];
extern sem_t sem_right_engine, sem_left_engine;

int main( void )
{
  engine_ptr right_engine, left_engine;
  int sem_r, sem_l;
  
  if (!robot_init()) return 1;
  
  identify_engines(&right_engine, &left_engine);
  
  sem_getvalue(&sem_right_engine, &sem_r);
  sem_getvalue(&sem_left_engine, &sem_l);
  
  printf("Sem right: %d Sem left: %d", sem_r, sem_l);
  turn_inplace_by_relative_angle(90, right_engine, left_engine);
  sleep(1);
  printf("Sem right: %d Sem left: %d", sem_r, sem_l);
  turn_inplace_by_relative_angle(-90, right_engine, left_engine);
  sleep(1);
  printf("Sem right: %d Sem left: %d", sem_r, sem_l);
  turn_inplace_by_relative_angle(180, right_engine, left_engine);
  sleep(1);
  printf("Sem right: %d Sem left: %d", sem_r, sem_l);
  turn_inplace_by_relative_angle(-180, right_engine, left_engine);
  sleep(1);
  printf("Sem right: %d Sem left: %d", sem_r, sem_l);
  
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
