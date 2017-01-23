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
 game_state gGameState = GAME_NOTSTARTED;
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

  }
  
  release_ball(&engines[ARM], 20);
  
#ifndef NO_BLUETOOTH
  int ball_x, ball_y;
  ball_x = robot_position.x + 10 * cosf(RAD(robot_position.head));
  ball_y = robot_position.y + 10 * sinf(RAD(robot_position.head));
  mod_btcom_send_BALL(DROP, ball_x, ball_y);
#endif
  
  while ((end_position_x - robot_position.x) > 10 || (end_position_y - robot_position.y) > 10) {
    move_by_offset(end_position_x - robot_position.x, end_position_y - robot_position.y, 500);

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
  
#ifndef NO_BLUETOOTH
  int ball_x, ball_y;
  ball_x = robot_position.x + 10 * cosf(RAD(robot_position.head));
  ball_y = robot_position.y + 10 * sinf(RAD(robot_position.head));
  mod_btcom_send_BALL(PICKUP, ball_x, ball_y);
#endif
  
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
  else if (side == 'l'){
    pos1_x = BIG_BEGINNER_LEFT_POS1_X;
    pos1_y = BIG_BEGINNER_LEFT_POS1_Y; 
    pos2_x = BIG_BEGINNER_LEFT_POS2_X; 
    pos2_y = BIG_BEGINNER_LEFT_POS2_Y;
    pos3_x = BIG_BEGINNER_LEFT_POS3_X;
    pos3_y = BIG_BEGINNER_LEFT_POS3_Y;
    end_x  = BIG_BEGINNER_LEFT_END_X;
    end_y  = BIG_BEGINNER_LEFT_END_Y;
  }
  
  move_by_offset(pos1_x - robot_position.x, pos1_y - robot_position.y, 400);
  print_position();

  move_by_offset(pos2_x - robot_position.x, pos2_y - robot_position.y, 400);
  print_position();

  move_by_offset(pos3_x - robot_position.x, pos3_y - robot_position.y, 400);
  print_position();
  
  if (side == 'r')
    turn_inplace_by_relative_angle(-180, 300);
  else if (side == 'l')
    turn_inplace_by_relative_angle(+195, 300);
  
  release_ball(&engines[ARM], 30);
  print_position();
#ifndef NO_BLUETOOTH
  int ball_x, ball_y;
  ball_x = robot_position.x + 30 * cosf(RAD(robot_position.head));
  ball_y = robot_position.y + 30 * sinf(RAD(robot_position.head));
  mod_btcom_send_BALL(DROP, ball_x, ball_y);
#endif
  
  move_by_offset(end_x - robot_position.x, end_y - robot_position.y, 400);
  print_position();
 }


void big_finisher(char side, char starting_point){
  int pos1_x = 0, pos2_x = 0, pos3_x = 0;
  int pos1_y = 0, pos2_y = 0, pos3_y = 0;
  int end_x = 0;
  int end_y = 0;
  
  if (side == 'r')
  {
    pos1_x = BIG_FINISHER_RIGHT_POS1_X;
    pos1_y = BIG_FINISHER_RIGHT_POS1_Y;
    pos2_x = BIG_FINISHER_RIGHT_POS2_X;
    pos2_y = BIG_FINISHER_RIGHT_POS2_Y; 
    end_x  = BIG_FINISHER_RIGHT_END_X;
    end_y  = BIG_FINISHER_RIGHT_END_Y;
  }
  else if (side == 'l'){
    pos1_x = BIG_FINISHER_LEFT_POS1_X;
    pos1_y = BIG_FINISHER_LEFT_POS1_Y;
    pos2_x = BIG_FINISHER_LEFT_POS2_X;
    pos2_y = BIG_FINISHER_LEFT_POS2_Y;
    pos3_x = 0;
    pos3_y = 0;
    end_x  = BIG_FINISHER_LEFT_END_X;
    end_y  = BIG_FINISHER_LEFT_END_Y;
  }
  else
    return;
  
  move_by_offset(pos1_x - robot_position.x, pos1_y - robot_position.y, 100);
  print_position();
  
  if (side == 'r')
    turn_inplace_by_relative_angle(-(-35 - robot_position.head), 200);
  else
    turn_inplace_by_relative_angle(-(-160 - robot_position.head), 200);
  print_position();

  
  search_and_grab(&engines[ARM]);
  print_position();
#ifndef NO_BLUETOOTH
  int ball_x, ball_y;
  ball_x = robot_position.x + 10 * cosf(RAD(robot_position.head));
  ball_y = robot_position.y + 10 * sinf(RAD(robot_position.head));
  mod_btcom_send_BALL(PICKUP, ball_x, ball_y);
#endif

  
  move_by_offset(pos2_x - robot_position.x, pos2_y - robot_position.y, 100);
  print_position();
  
  
  if (side == 'r')
    turn_inplace_by_relative_angle(-(-35 - robot_position.head), 200);
  else
    turn_inplace_by_relative_angle(-(-90 - robot_position.head), 200);
  print_position();

  
  move_by_offset(end_x - robot_position.x, end_y - robot_position.y, 100);
  print_position();
}


  