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

#include "globals.h"

#include "utilities.h"
#include "tacho.h"
#include "movement.h"
#include "init.h"
//#include "test.h"
#include "grabber.h"
#include "obstacle_detection.h"
#include "odometry.h"

#include "mjolnir.h"

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

void TEST1(void)
{
  //TEST 1
  go_straight_dist(160, 500,1);
}

void TEST2(void)
{
  //TEST 2
  go_straight_dist(87, 400,1);
  turn_inplace_by_relative_angle(-90, 200);
  go_straight_dist(23, 100, 1);
  release_ball(&engines[ARM], 23);
  turn_inplace_by_relative_angle(90, 200);
  go_straight_dist(75, 400, 1);
}
  
void TEST3(void)
{
  //TEST 3
  go_straight_dist(100, 500, 1);
  turn_inplace_by_relative_angle(90, 200);
  go_straight_dist(75, 500, 1);
  turn_inplace_by_relative_angle(-90, 200);
  go_straight_dist(85, 500, 1);
  turn_inplace_by_relative_angle(+90, 200);
  go_straight_dist(-60, 500, 1);
  turn_inplace_by_relative_angle(-90, 200);
  go_straight_dist(180, 500, 1);
}

void TEST4(void)
{
  //TEST 3
  go_straight_dist(100, 300, 1);
  turn_inplace_by_relative_angle(90, 200);
  go_straight_dist(75, 300, 1);
  turn_inplace_by_relative_angle(-90, 200);
  go_straight_dist(90, 300, 1);
  turn_inplace_by_relative_angle(+90, 200);
  go_straight_dist(-45, 300, 1);
  release_ball(&engines[ARM], 15);
  turn_inplace_by_relative_angle(-90, 200);
  go_straight_dist(180, 300, 1);
}
  //grab_ball(&engines[ARM]);
  
void TEST5(void){
  //TEST 5
  //go_straight_dist(87, 400, 1);
  //turn_inplace_by_relative_angle(-90, 200);
  //go_straight_dist(10, 100, 1);
  grab_ball(&engines[ARM], 200);
  //go_straight(time, -50, 1);
  //turn_inplace_by_relative_angle(90, 200);
  //go_straight_dist(75, 400, 1);
}

/**
 * main role area part
 */
int main( int argc, char* argv[] )
{
  
  
  
	//if ( argc < 5 ) {
		//printf("Usage: %s [role] [area] [part] [action]\n", argv[0] );
		//printf("Options:\n");
		//printf("    role: 'b' or 'f' or 'g'(beginner or finisher, or (just for test) grabber)\n");
		//printf("    area: 'l' or 's' (large or small)\n");
		//printf("    part: 'l' or 'r' (left or right, valid only with LARGE area.)\n");
		//printf("    action: 'g' or 'b' (just Go or place a Ball)\n");

		//return 1;
	//}

	if (!robot_init()) return 1;
  msleep(1000);
  
  robot_position.x = BEGINNER_RIGHT_START_X;
  robot_position.y = BEGINNER_RIGHT_START_Y;
  
  small_beginner('r');
  small_finisher('r');

  //print_position();
  //go_straight_dist(10, 100, 1);
  //print_position();
  //go_straight_dist(20, 100, 1);
  //print_position();
  //go_straight_dist(30, 100, 1);
  //print_position();
  //turn_inplace_by_relative_angle(90, 100);
  //print_position();
  //search_and_grab(&engines[ARM]);
  //grab_ball(&engines[ARM], min_distance/10-22);
  
  //turn_inplace_by_relative_angle(-30, 500);
  //int angle;
  //for (angle = 0; angle < 60; angle += 5)
  //{
    ////set_port_mode(us->address, "US-SI-CM");
    ////msleep(500);
    //msleep(500);
    //int sum = us->distance;
    //msleep(500);
    //sum += us->distance;
    //msleep(500);
    //sum += us->distance;

    
    //printf("Distance AVG: %d\n", sum/3);
    
    //if ((sum/3) < 400) {
      ////turn_inplace_by_relative_angle(-5, 50);
        //printf("DETECTED\n");
      //grab_ball(&engines[ARM], (sum/3)/10);
      //break;
    //}
    //turn_inplace_by_relative_angle(+5, 50);
  //}
  

  //TEST5();

  
  //go_straight_dist(100, 300, 1);
  //turn_inplace_by_relative_angle(90, 200);
  //go_straight_dist(75, 300, 1);
  //turn_inplace_by_relative_angle(-90, 200);
  //go_straight_dist(90, 300, 1);
  
  //set_sensor_mode(gyro->address, "GYRO-CAL");
  //msleep(1000);
  //set_sensor_mode(gyro->address, "GYRO-G&A");
  
  //turn_inplace_by_relative_angle(+90, 200);
  //go_straight_dist(-45, 300, 1);
  //release_ball(&engines[ARM], 15);
  //turn_inplace_by_relative_angle(-90, 200);
  //go_straight_dist(180, 300, 1);
  
  //set_sensor_mode(gyro->address, "GYRO-CAL");
  //msleep(1000);
  //set_sensor_mode(gyro->address, "GYRO-G&A");
  
  //turn_inplace_by_relative_angle(+90, 200);
  //go_straight_dist(70, 300, 1);
  //turn_inplace_by_relative_angle(+90, 200);
  
  //set_sensor_mode(gyro->address, "GYRO-CAL");
  //msleep(1000);
  //set_sensor_mode(gyro->address, "GYRO-G&A");
  
  //go_straight_dist(100, 300, 1);
  //turn_inplace_by_relative_angle(90, 200);
  //go_straight_dist(75, 300, 1);
  //turn_inplace_by_relative_angle(-90, 200);
  //go_straight_dist(85, 300, 1);
  
  //set_sensor_mode(gyro->address, "GYRO-CAL");
  //msleep(1000);
  //set_sensor_mode(gyro->address, "GYRO-G&A");
  
  //turn_inplace_by_relative_angle(-90, 200);
  //grab_ball(&engines[ARM]);
  //go_straight_dist(20, 300, 1);
  
  //set_sensor_mode(gyro->address, "GYRO-CAL");
  //msleep(1000);
  //set_sensor_mode(gyro->address, "GYRO-G&A");

  //turn_inplace_by_relative_angle(+90, 200);
  //go_straight_dist(180, 300, 1);
  
  
	///* BEGINNER + SMALL */
	//if ( (strcmp(argv[1], "b") == 0) && (strcmp(argv[2], "s") == 0) ) {
		//if ( strcmp(argv[4], "g") == 0 ) { /* Just go */
			//printf("TEST 1 start!\n");
			//TEST1();
			//printf("Mission completed!\n");
			//return 1;
		//} else if ( strcmp(argv[4], "b") == 0 ) { /* with placing the ball */
			//printf("TEST 2 start!\n");
			//TEST2();
			//printf("Mission completed!\n");
			//return 1;
		//}

	//} 
	///* BEGINNER + LARGE */
	//if ( (strcmp(argv[1], "b") == 0) && (strcmp(argv[2], "l") == 0) ) {
		//if ( strcmp(argv[4], "g") == 0 ) { /* Just go */
			//printf("TEST 3 start!\n");
			//TEST3();
			//printf("Mission completed!\n");
			//return 1;
		//} else if ( strcmp(argv[4], "b") == 0 ) { /* with placing the ball */
			//printf("TEST 4 start!\n");
			//TEST4();
			//printf("Mission completed!\n");
			//return 1;
		//}
	//}

	///* GRABBER TEST */
	//if (strcmp(argv[1], "g") == 0)  {
		//printf("TEST 5 start!\n");
		//TEST5();
		//printf("Mission completed!\n");
		//return 1;
	//}
	
  //sleep(2);
  
  
  //go_straight(10000, 500);
  //go_straight(10000, 300);
  //go_straight(10000, 300);
  //go_straight(10000, 300);
  //go_straight(10000, 300);
  
  
  
  
  threads_deinit();
  ev3_uninit();
  printf( "*** ( EV3 ) Bye! ***\n" );
  
  return 0;
}


