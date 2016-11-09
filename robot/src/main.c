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
  

  turn_engine_arg_struct right_engine_args, left_engine_args;
  pthread_t right_tid, left_tid;
  

  right_engine_args.angle = angle;
  right_engine_args.engine = right_engine;
  right_engine_args.speed_mod = 16;
  
  printf("MAIN : %d %d %d\n",right_engine_args.angle, right_engine_args.engine, right_engine_args.speed_mod);
  
  left_engine_args.angle = -angle;
  left_engine_args.engine = left_engine;
  left_engine_args.speed_mod = 16;
  
  pthread_create(&right_tid, NULL, thread_turn_engine, (void*)&right_engine_args);
  //pthread_create(&left_tid,  NULL, thread_turn_engine, (void*)&left_engine_args);
  
  pthread_join(right_tid, NULL);
  //pthread_join(left_tid, NULL);
  
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}
