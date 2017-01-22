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
#include "mod_btcom.h"

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
int main (int argc, char* argv[]) {
  
  char arena[25];
  if (argc != 2) {
    printf("Please, specify the arena\n");
    return -1;
  }
  memcpy(arena, argv[1], 25);
  printf("Playing in the %s arena\n", arena);

	/* Initializing the robot */
	if (!robot_init()) return 1;
	msleep(1000);
  
  //robot_position.x = BIG_BEGINNER_LEFT_START_X;
  //robot_position.y = BIG_BEGINNER_LEFT_START_Y;
  //robot_position.head = 90;

  //big_beginner('l', '0');

  
  //return 0;
  

  sleep(2);
	/* until get the role */
	printf("My role: %d, my side: %d, my team mate ID: %d\n", gMyRole, gMySide, gTeamMateId);

	/* Change state */
	gMyState = STARTED;
  gGameState = GAME_STARTED;
  if (!memcmp(arena, "small", 5)) {
    /*=====================================================================================
                                      SMALL ARENA
     =====================================================================================*/
    printf("SMALL\n");
    char starting_position;
    
    if (gMyRole ==  BEGINNER){
      
      starting_position = 'r';
      printf("I'm playing as BEGINNER in SMALL arena\n");
      gMyState = RUNNING;
      small_beginner(starting_position);
      gMyRole = FINISHER;
      gMyState = WAITING;
    }
    else {
      starting_position = 'l';
    }
    
    while (gGameState == GAME_RUN) {
      pthread_mutex_lock(&bt_mutex);
      while (gMyState != READY){
        pthread_cond_wait(&cv_next, &bt_mutex);
      }
      gMyState = RUNNING;
      pthread_mutex_unlock(&bt_mutex);
      if (gMyRole == BEGINNER) {
        printf("I'm playing as BEGINNER in SMALL arena - side: %c\n", starting_position);
        gMyState = RUNNING;
        small_beginner(starting_position);
        gMyRole = FINISHER;
        gMyState = WAITING;
        printf("Sending NEXT message to team mate: %d\n", gTeamMateId);
        mod_btcom_send_NEXT(gTeamMateId);

      }
      else if (gMyRole == FINISHER) {
        printf("I'm playing as FINISHER in SMALL arena - side: %c\n", starting_position);
        gMyState = RUNNING;
        small_finisher(starting_position);
        gMyRole = BEGINNER;
        gMyState = WAITING;
        printf("Sending NEXT message to team mate: %d\n", gTeamMateId);
        mod_btcom_send_NEXT(gTeamMateId);
      }
    }
    
  }
  else if (!memcmp(arena, "big", 3)) {
    /*=====================================================================================
                                      BIG ARENA
     =====================================================================================*/
    printf("BIG\n");
    char starting_position;
    if (gMySide == 0) {
      starting_position = 'r';
      if (gMyRole == BEGINNER) {
        robot_position.x = BIG_BEGINNER_RIGHT_START_X;
        robot_position.y = BIG_BEGINNER_RIGHT_START_Y;
        robot_position.head = 90;
      }
      else {
        robot_position.x = BIG_FINISHER_RIGHT_START_X;
        robot_position.y = BIG_FINISHER_RIGHT_START_Y;
        robot_position.head = -90;
      }
    }
    else if (gMySide == 1){
      starting_position = 'l';
      if (gMyRole == BEGINNER) {
        robot_position.x = BIG_BEGINNER_LEFT_START_X;
        robot_position.y = BIG_BEGINNER_LEFT_START_Y;
        robot_position.head = 90;
      }
      else {
        robot_position.x = BIG_FINISHER_LEFT_START_X;
        robot_position.y = BIG_FINISHER_LEFT_START_Y;
        robot_position.head = -90;
      }
    }
    else
      return -1;
    
    gMyState = STARTED;
    gGameState = GAME_RUN;
    printf("SETUP DONE -- WE CAN START\n");
    
    if (gMyRole ==  BEGINNER){
      printf("I'm playing as BEGINNER in BIG arena\n");
      gMyState = RUNNING;
      big_beginner(starting_position, 'x');
      gMyRole = FINISHER;
      gMyState = WAITING;
      mod_btcom_send_NEXT(gTeamMateId);
    }

    
    while (gGameState == GAME_RUN) {
      pthread_mutex_lock(&bt_mutex);
      printf("Waiting for running\n");
      while (gMyState != READY){
        pthread_cond_wait(&cv_next, &bt_mutex);
      }
      gMyState = RUNNING;
      pthread_mutex_unlock(&bt_mutex);
      if (gMyRole == BEGINNER) {
        printf("I'm playing as BEGINNER in BIG arena - side: %c\n", starting_position);
        gMyState = RUNNING;
        big_beginner(starting_position, 'x');
        gMyRole = FINISHER;
        gMyState = WAITING;

        mod_btcom_send_NEXT(gTeamMateId);
        
      }
      else if (gMyRole == FINISHER) {
        printf("I'm playing as FINISHER in BIG arena - side: %c\n", starting_position);
        gMyState = RUNNING;
        big_finisher(starting_position, 'x');
        gMyRole = BEGINNER;
        gMyState = WAITING;
        mod_btcom_send_NEXT(gTeamMateId);
      }
    }
    
  }
  
	///* START */
//#ifdef BIG_ARENA
	//if ((gMyRole == BEGINNER) && (gMySide == LEFT)){
		//printf("I'm playing as BEGINNER in LEFT side\n");
		////left_beginner('r');/*TODO: @Simone: change the param!*/
	//} else if ((gMyRole == BEGINNER) && (gMySide == RIGHT)) {
		//printf("I'm playing as BEGINNER in RIGHT side\n");
		////right_beginner('r');/*TODO: @Simone: change the param!*/
	//} else if ((gMyRole == FINISHER) && (gMySide == LEFT)) {
		//printf("I'm playing as FINISHER in LEFT side\n");
		////left_finisher('r');/*TODO: @Simone: change the param!*/
	//} else if ((gMyRole == FINISHER) && (gMySide == RIGHT)) {
		//printf("I'm playing as FINISHER in RIGHT side\n");
		////right_finisher('r');/*TODO: @Simone: change the param!*/
//#else /* SMALL ARENA*/
	//if (gMyRole == BEGINNER) {
		//printf("I'm playing as BEGINNER in SMALL arena\n");
    //gMyState = RUNNING;
      //small_beginner('r');/*TODO: @Simone: change the param!*/
    //gMyState = DONE;
	//} else if (gMyRole == FINISHER) {
		//printf("I'm playing as FINISHER in SMALL arena\n");
    //pthread_mutex_lock(&bt_mutex);
    //while (gMyState != READY){
      //pthread_cond_wait(&cv_next, &bt_mutex);
    //}
    //gMyState = RUNNING;
    //pthread_mutex_unlock(&bt_mutex);
		//small_finisher('l');/*TODO: @Simone: change the param!*/
    //gMyState = DONE;
//#endif /* BIG_ARENA */
	//} else {
		//printf("Wrong role and/or side, my friend! Cannot move!\n");
	//}

	///* Waiting for messages sent by server and others */
    ////pthread_create(&tid, NULL, __mod_btcom_wait_messages, NULL);

	///* Periodically send the location */
    ////pthread_create(&tid2, NULL, __mod_btcom_send_location, NULL);

    ////printf("Bluetooth communication started\n");

	//while (1) {
		///* Send the signal to server at the end of journey */
		//if (gMyState == DONE) {
			//printf("Sending NEXT message to team mate: %d\n", gTeamMateId);
			//mod_btcom_send_NEXT(gTeamMateId);
			//printf("I become a FINISHER now\n");
			//gMyRole = FINISHER;
			//gMyState = WAITING;
		//}

		//if ( (gMyState == STOPPED) && (gMyState == KICKED) ) {
			//printf("We are done! Gotta stop now!\n");
			//break;
		//}
		///* Loop every 1 second */
		//sleep(1);
	//}

    //pthread_join(tid, NULL);
    //pthread_join(tid2, NULL);

	threads_deinit();
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return 0;
}