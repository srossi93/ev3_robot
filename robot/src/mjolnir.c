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
  return;
}


void big_beginner(char side, char starting_point){
  int pos1_x = 0, pos2_x = 0, pos3_x = 0;
  int pos1_y = 0, pos2_y = 0, pos3_y = 0;
  int end_x = 0;
  int end_y = 0;
  
  if (side == 'r')
  {
    pos1_x = BIG_BEGINNER_RIGHT_POS1_X;
    pos1_y = BIG_BEGINNER_RIGHT_POS1_Y;
    pos2_x = BIG_BEGINNER_RIGHT_POS2_X;
    pos2_y = BIG_BEGINNER_RIGHT_POS2_Y;
    pos3_x = BIG_BEGINNER_RIGHT_POS3_X;
    pos3_y = BIG_BEGINNER_RIGHT_POS3_Y;
    end_x  = BIG_BEGINNER_RIGHT_END_X;
    end_y  = BIG_BEGINNER_RIGHT_END_Y;
  }
  
  do {
    move_by_offset(pos1_x - robot_position.x, pos1_y - robot_position.y, 500);
  } while (0);

  do {
    move_by_offset(pos2_x - robot_position.x, pos2_y - robot_position.y, 500);
  } while (0);
  
  
  do {
    move_by_offset(pos3_x - robot_position.x, pos3_y - robot_position.y, 500);
  } while (0);
  
  turn_inplace_by_relative_angle(-180, 200);
  
  release_ball(&engines[ARM], 25);
  
  do {
    move_by_offset(end_x - robot_position.x, end_y - robot_position.y, 500);
  } while (0);
  
}
 