//
//  mjolnir.c
//  robot
//
//  Created by Simone Rossi on 16/01/17.
//  Copyright © 2017 Simone Rossi. All rights reserved.
//

#include <stdio.h> 
#include "mjolnir.h"
#include <math.h>

int msgId = 0;
robot_state gMyState = NOTSTARTED;
unsigned char gMyRole, gMySide, gTeamMateId;  

void small_beginner(char starting_point){
  
  
  int target_position_x = 0, target_position_y = 0;
  int end_position_x = 0, end_position_y = 0;
  
  if (starting_point == 'r') {
    
    target_position_x = BEGINNER_RIGHT_LEAVE_X;
    target_position_y = BEGINNER_RIGHT_LEAVE_Y;
    end_position_x    = BEGINNER_RIGHT_END_X;
    end_position_y    = BEGINNER_RIGHT_END_Y;
    
  }
  else if (starting_point == 'l') {
    
    target_position_x = BEGINNER_LEFT_LEAVE_X; 
    target_position_y = BEGINNER_LEFT_LEAVE_Y;
    end_position_x    = BEGINNER_LEFT_END_X;
    end_position_y    = BEGINNER_LEFT_END_Y;
  }
  
  while ((target_position_x - robot_position.x) > 10 || (target_position_y - robot_position.y) > 10) {
     move_by_offset(target_position_x - robot_position.x, target_position_y - robot_position.y, 500);
    print_position();
  }
  
  release_ball(&engines[ARM], 20);
  
  while ((end_position_x - robot_position.x) > 10 || (end_position_y - robot_position.y) > 10) {
    move_by_offset(end_position_x - robot_position.x, end_position_y - robot_position.y, 500);
        print_position();
  }
  
  return;
}

void small_finisher(char starting_point){
  
  
  int target_position_x = 0, target_position_y = 0;
  int end_position_x = 0, end_position_y = 0;
  
  if (starting_point == 'r') {
    
    target_position_x = FINISHER_RIGHT_SEARCH_X;
    target_position_y = FINISHER_RIGHT_SEARCH_Y;
    end_position_x    = FINISHER_RIGHT_END_X;
    end_position_y    = FINISHER_RIGHT_END_Y;
    
  }
  else if (starting_point == 'l') {
    
    target_position_x = FINISHER_LEFT_SEARCH_X;
    target_position_y = FINISHER_LEFT_SEARCH_Y;
    end_position_x    = FINISHER_LEFT_END_X;
    end_position_y    = FINISHER_LEFT_END_Y;
  }
  do {
    move_by_offset(target_position_x - robot_position.x, target_position_y - robot_position.y, 500);
  } while ((target_position_x - robot_position.x) > 10 || (target_position_y - robot_position.y) > 10);
  
  search_and_grab(&engines[ARM]);
  
  do  {
    move_by_offset(end_position_x - robot_position.x, end_position_y - robot_position.y + 7, 500);
  } while (fabsf(end_position_x - robot_position.x) > 10 || fabsf(end_position_y - robot_position.y) > 10);
  
  
  
  
  

  
  //if (starting_point == 'r') {
    //move_by_offset(FINISHER_RIGHT_SEARCH_X - robot_position.x, FINISHER_RIGHT_SEARCH_Y - robot_position.y, 500);
    
    //search_and_grab(&engines[ARM]);

    //move_by_offset(FINISHER_RIGHT_END_X - robot_position.x, FINISHER_RIGHT_END_Y - robot_position.y, 500);
  //}
  //else if (starting_point == 'l') {
    //move_by_offset(FINISHER_LEFT_SEARCH_X - robot_position.x, FINISHER_LEFT_SEARCH_Y - robot_position.y, 500);
    
    
    
    //move_by_offset(FINISHER_LEFT_END_X - robot_position.x, FINISHER_LEFT_END_Y - robot_position.y, 500);
  //}
  return;
}

 