//
//  mjolnir.c
//  robot
//
//  Created by Simone Rossi on 16/01/17.
//  Copyright © 2017 Simone Rossi. All rights reserved.
//

#include <stdio.h>
#include "mjolnir.h"


void small_beginner(char starting_point){
  
  if (starting_point == 'r') {
    move_by_offset(BEGINNER_RIGHT_LEAVE_X - robot_position.x, BEGINNER_RIGHT_LEAVE_Y - robot_position.y, 500);

    release_ball(&engines[ARM], 20);

    move_by_offset(BEGINNER_RIGHT_END_X - robot_position.x, BEGINNER_RIGHT_END_Y - robot_position.y, 500);
  }
  else if (starting_point == 'l') {
    move_by_offset(BEGINNER_LEFT_LEAVE_X - robot_position.x, BEGINNER_LEFT_LEAVE_Y - robot_position.y, 500);
    
    release_ball(&engines[ARM], 20);
    
    move_by_offset(BEGINNER_LEFT_END_X - robot_position.x, BEGINNER_LEFT_END_Y - robot_position.y, 500);

  }
  return;
}

void small_finisher(char starting_point){
  if (starting_point == 'r') {
    move_by_offset(FINISHER_RIGHT_SEARCH_X - robot_position.x, FINISHER_RIGHT_SEARCH_Y - robot_position.y, 500);
    
    search_and_grab(&engines[ARM]);

    move_by_offset(FINISHER_RIGHT_END_X - robot_position.x, FINISHER_RIGHT_END_Y - robot_position.y, 500);
  }
  else if (starting_point == 'l') {
    move_by_offset(FINISHER_LEFT_SEARCH_X - robot_position.x, FINISHER_LEFT_SEARCH_Y - robot_position.y, 500);
    
    search_and_grab(&engines[ARM]);
    
    move_by_offset(FINISHER_LEFT_END_X - robot_position.x, FINISHER_LEFT_END_Y - robot_position.y, 500);
  }
  return;
}