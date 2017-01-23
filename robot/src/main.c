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
    printf(" [MAIN] Please, specify the arena\n");
    return -1;
  }
  memcpy(arena, argv[1], 25);
  printf(" [MAIN] Playing in the %s arena\n", arena);

	/* Initializing the robot */
	if (!robot_init()) return 1;
  msleep(1000);
  
  //robot_position.x = BIG_BEGINNER_LEFT_START_X;
  //robot_position.y = BIG_BEGINNER_LEFT_START_Y;
  //robot_position.head = 90;

  //big_beginner('l', '0');

  
  //return 0;
  
  //while (gGameState == GAME_NOTSTARTED) {
  //  msleep(250);
  //}
  //msleep(2000);
  /* until get the role */
	printf(" [MAIN] My role: %d, my side: %d, my team mate ID: %d\n", gMyRole, gMySide, gTeamMateId);

	/* Change state */
	gMyState = STARTED;
  gGameState = GAME_STARTED;
  if (!memcmp(arena, "small", 5)) {
    /*=====================================================================================
                                      SMALL ARENA
     =====================================================================================*/
    //printf("SMALL\n");
    char starting_position;
    
    printf(" [DEBUG] SETUP INITIAL POSITION\n");
    
    if (gMyRole == BEGINNER) {
      starting_position = 'r';
      robot_position.x = BEGINNER_RIGHT_START_X;
      robot_position.y = BEGINNER_RIGHT_START_Y;
      robot_position.head = 90;
    }
    else {
      starting_position = 'l';
      robot_position.x = FINISHER_LEFT_START_X;
      robot_position.y = FINISHER_LEFT_START_Y;
      robot_position.head = -90;
    }
    
    
    gMyState = STARTED;
    gGameState = GAME_RUN;
    printf(" [DEBUG] SETUP DONE -- WE CAN START\n");
    
    if (gMyRole ==  BEGINNER){
      
      //      starting_position = 'r';
      printf(" [MAIN] I'm playing as BEGINNER in SMALL arena\n");
      gMyState = RUNNING;
      small_beginner(starting_position);
      gMyRole = FINISHER;
      mod_btcom_send_NEXT(gTeamMateId);

    }
    gMyState = WAITING;   
    
    while (gGameState == GAME_RUN) {
      

      if (gMyRole == BEGINNER) {
        
        printf(" [MAIN] I'm playing as BEGINNER in SMALL arena - side: %c\n", starting_position);
        gMyState = RUNNING;
        small_beginner(starting_position);
        gMyRole = FINISHER;
        gMyState = WAITING;
        printf(" [MAIN] Sending NEXT message to team mate: %d\n", gTeamMateId);
        mod_btcom_send_NEXT(gTeamMateId);

      }
      else if (gMyRole == FINISHER) {
        printf(" [MAIN] Waiting for running\n");
        
        pthread_mutex_lock(&bt_mutex);
        while (gMyState != READY){
          pthread_cond_wait(&cv_next, &bt_mutex);
          if (gGameState != GAME_RUN) {
            printf(" [MAIN] Exit\n");
            goto __EXIT;
          }
        }
        pthread_mutex_unlock(&bt_mutex);
        
        printf(" [MAIN] I'm playing as FINISHER in SMALL arena - side: %c\n", starting_position);
        gMyState = RUNNING;
        small_finisher(starting_position);
        gMyRole = BEGINNER;
        gMyState = WAITING;


      }
    }
    
  }
  
  
  
  
  
  
  
  
  
  else if (!memcmp(arena, "big", 3)) {
    /*=====================================================================================
                                      BIG ARENA
     =====================================================================================*/
    
    printf(" [DEBUG] SETUP INITIAL POSITION\n");

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

    printf(" [DEBUG] SETUP DONE -- WE CAN START\n");
    
    if (gMyRole ==  BEGINNER){
      printf(" [MAIN] I'm playing as BEGINNER in BIG arena\n");
      gMyState = RUNNING;
      big_beginner(starting_position, 'x');
      gMyRole = FINISHER;
      gMyState = WAITING;
      mod_btcom_send_NEXT(gTeamMateId);
    }
    
    gMyState = WAITING;

    
    while (gGameState == GAME_RUN) {
      
      pthread_mutex_lock(&bt_mutex);
      printf(" [MAIN] Waiting for running\n");
      while (gMyState != READY){
        pthread_cond_wait(&cv_next, &bt_mutex);
        if (gGameState != GAME_RUN) {
          goto __EXIT;
        }
      }
      gMyState = RUNNING;
      pthread_mutex_unlock(&bt_mutex);
      if (gMyRole == BEGINNER) {
        
        printf(" [MAIN] I'm playing as BEGINNER in BIG arena - side: %c\n", starting_position);
        gMyState = RUNNING;
        big_beginner(starting_position, 'x');
        gMyRole = FINISHER;
        gMyState = WAITING;

        mod_btcom_send_NEXT(gTeamMateId);
        
      }
      else if (gMyRole == FINISHER) {
        printf(" [MAIN] I'm playing as FINISHER in BIG arena - side: %c\n", starting_position);
        gMyState = RUNNING;
        big_finisher(starting_position, 'x');
        gMyRole = BEGINNER;
        gMyState = WAITING;
        mod_btcom_send_NEXT(gTeamMateId);
      }
    }
    
  }
  
	
__EXIT:

	threads_deinit();
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return 0;
}