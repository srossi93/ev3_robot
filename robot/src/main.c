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

void detect_obstacles(void)
{
	while ( (engines[L].state != 0 ) && (engines[R].state != 0) ) {
		if (us->distance <= 200) {
			printf("Stop engines\n");
			stop_engines();
			return;
		}
		msleep(100);
		printf("state left = %d, state right = %d\n", engines[L].state, engines[R].state);
	}
}

/**
 * main role area part
 */
int main( int argc, char* argv[] )
{
#if 0
	char role[20];
	char area[20];
	char part[20];
#endif
	if (!robot_init()) return 1;
  
	//sleep(2);

  /* Go straight */
	printf("Go straight for 10 seconds\n");
	//printf("Go straight for 500 centimets\n");
	//go_straight_dist(1, 300);
	___go_straight(10000, 100);
	/* continuously check if there a obstacles */
#if 1
	printf("Detecting obstacles...\n");
	detect_obstacles();
	//sleep(1);
	/*stop */
	//printf("Stop engines\n");
	//stop_engines();
	//sleep(5);
  /* Turn right */
 	//turn_right(); 
	printf("Turn right\n");
	turn_inplace_by_relative_angle(90, 100);
  /* Go straight for 100 centimets*/
  	//go_straight_dist(1000);
	printf("Go straight for 5 seconds\n");
	___go_straight(5000, 100);
	/* continuously check if there a obstacles */
	printf("Detecting obstacles...\n");
	detect_obstacles();
  /* Turn left */
  	//turn_left();
	turn_inplace_by_relative_angle(-90, 100);
  /* Go straight for 50 centimets */
  	//go_straight_dist(500);
	printf("Go straight for 10 seconds\n");
	___go_straight(10000, 100);
	/* continuously check if there a obstacles */
	detect_obstacles();
  /*  */
#endif
  /*  */
  
  /*  */
  
  //grab_ball(&engines[ARM]);
  
  threads_deinit();
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}


