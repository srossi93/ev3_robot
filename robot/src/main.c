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

int main( void )
{
  engine_ptr right_engine, left_engine;
  int angle = 90;
  if (!robot_init()) return 1;
  

  identify_engines(&right_engine, &left_engine);
  
  turn_inplace_by_relative_angle(90, right_engine, left_engine);
  usleep(5000);
  turn_inplace_by_relative_angle(-90, right_engine, left_engine);
  usleep(5000);
  turn_inplace_by_relative_angle(180, right_engine, left_engine);
  usleep(5000);
  turn_inplace_by_relative_angle(-180, right_engine, left_engine);
  usleep(5000);
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
