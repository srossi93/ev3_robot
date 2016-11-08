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
  engine_ptr r_eng, l_eng;
  
  if (!robot_init()) return 1;
  

  identify_engines(&r_eng, &l_eng);
  

  int max_speed;
  get_tacho_max_speed(r_eng, &max_speed);
  
  set_tacho_speed_sp(r_eng, max_speed / 16);
  set_tacho_speed_sp(l_eng, max_speed / 16);
  
  set_tacho_ramp_up_sp(r_eng, 0);
  set_tacho_ramp_up_sp(l_eng, 0);
  
  set_tacho_ramp_down_sp(r_eng, 0);
  set_tacho_ramp_down_sp(l_eng, 0);
  
  set_tacho_position_sp(r_eng, 180);
  set_tacho_position_sp(l_eng, -180);
  
  set_tacho_command_inx(r_eng, TACHO_RUN_TO_REL_POS );
  set_tacho_command_inx(l_eng, TACHO_RUN_TO_REL_POS );
  
  
  
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}