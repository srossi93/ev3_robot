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
  
  move_by_offset(BEGINNER_RIGHT_LEAVE_X - robot_position.x, BEGINNER_RIGHT_LEAVE_Y - robot_position.y, 500);
  //search_and_grab(&engines[ARM]);
  release_ball(&engines[ARM], 20);
  move_by_offset(BEGINNER_RIGHT_END_X - robot_position.x, BEGINNER_RIGHT_END_Y - robot_position.y, 500);
  return;
}