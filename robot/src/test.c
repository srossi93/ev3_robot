//
//  test.c
//  robot
//
//  Created by Simone Rossi on 10/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include <test.h>

int test_turn_inplace_by_relative_angle() {
  
  engine_ptr right_engine, left_engine;
  
  if (!identify_engines(&right_engine, &left_engine)) return 1;
  
  int i = 0;
  for (i = 0; i < 8 ; i++)
  {
    turn_inplace_by_relative_angle(45, right_engine, left_engine);
  }
  for (i = 0; i < 4 ; i++)
  {
    turn_inplace_by_relative_angle(90, right_engine, left_engine);
  }
  for (i = 0; i < 2 ; i++)
  {
    turn_inplace_by_relative_angle(180, right_engine, left_engine);
  }
  turn_inplace_by_relative_angle(360, right_engine, left_engine);
 
  for (i = 0; i < 8 ; i++)
  {
    turn_inplace_by_relative_angle(-45, right_engine, left_engine);
  }
  for (i = 0; i < 4 ; i++)
  {
    turn_inplace_by_relative_angle(-90, right_engine, left_engine);
  }
  for (i = 0; i < 2 ; i++)
  {
    turn_inplace_by_relative_angle(-180, right_engine, left_engine);
  }
  turn_inplace_by_relative_angle(-360, right_engine, left_engine);
  
  return 0;
}