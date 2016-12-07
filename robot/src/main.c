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

extern pthread_cond_t cv_ball_detected;

int main( void )
{
  if (!robot_init()) return 1;
  
  //while (1)
  //{
    //msleep(1000);
    //printf("%d %d\n", gyro->angle, gyro->rot_speed);
  //}
  sleep(2);
  
  
  //turn_engine_arg_struct arg;
  //arg.speed = 50;
  //arg.time = 10000;
  //int i,ii,n,val;
  //char s[255];
  //for ( i = 0; i < DESC_LIMIT; i++ ) {
    //if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
      //if ( !strcmp(ev3_sensor_type( ev3_sensor[ i ].type_inx ), "lego-ev3-color") )
        //color->address=i;
        
    //}
  //}
  
  

  //while (1) {
    //msleep(500);
    ////pthread_mutex_lock(&color_mutex);
    //int tmp;
    //get_sensor_value(0, color->address, &tmp);
    //printf("Refl: %d\n", tmp);
    //get_sensor_value(0, gyro->address, &tmp);
    ///printf("Ang: %d\n", tmp);
    ////if (color->reflection > 10)
    ////  pthread_cond_signal(&cv_ball_detected);
    ////pthread_mutex_unlock(&color_mutex);
  //}
  
  test_square();
  
  deploy_arm(&engines[ARM]);
  
  open_arm(&engines[ARM]);
  
  
  pthread_t check_tid, run_tid;
  turn_engine_arg_struct arg;
  arg.time = 30000;
  arg.speed = 100;
  pthread_create(&run_tid, NULL, __go_straight, (void*)&arg);
  pthread_create(&check_tid, NULL, __check_ball, NULL);
 
  int i;
  for (i = 0; i < 30000; i+=250) {
    if (ball_found) {
      printf("BALL detected\n");
      pthread_cancel(run_tid);
      break;
    }
    msleep(250);
  }
  
  pthread_join(run_tid, NULL);
  pthread_cancel(check_tid);

  
  printf("done\n");
  
  
  
  
  
  write_stop_action(&(engines[R]), TACHO_BRAKE);
  write_stop_action(&(engines[L]), TACHO_BRAKE);
  
  write_command(&(engines[R]), TACHO_STOP);
  write_command(&(engines[L]), TACHO_STOP);
  
  
  close_arm(&engines[ARM]);
  
  undeploy_arm(&engines[ARM]);
  
  //  }
  
  



  
  threads_deinit();
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}


