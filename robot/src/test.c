//
//  test.c
//  robot
//
//  Created by Simone Rossi on 10/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#include <test.h>

void test_turn_inplace_by_relative_angle() {
  
  
  int i = 0;
  for (i = 0; i < 8 ; i++)
  {
    turn_inplace_by_relative_angle(45, 700);
    msleep(500);
  }
  for (i = 0; i < 4 ; i++)
  {
    turn_inplace_by_relative_angle(90, 700);
        msleep(500);
  }
  for (i = 0; i < 2 ; i++)
  {
    turn_inplace_by_relative_angle(180, 700);
        msleep(500);
  }
  turn_inplace_by_relative_angle(360, 700);
      msleep(500);
 
  for (i = 0; i < 8 ; i++)
  {
    turn_inplace_by_relative_angle(-45, 700);
        msleep(500);
  }
  for (i = 0; i < 4 ; i++)
  {
    turn_inplace_by_relative_angle(-90, 700);
        msleep(500);
  }
  for (i = 0; i < 2 ; i++)
  {
    turn_inplace_by_relative_angle(-180, 700);
        msleep(500);
  }
  turn_inplace_by_relative_angle(-360, 700);
      msleep(500);
  
}

void test_square(){
  int i;
  for (i = 0; i < 4*3; i++) {
    go_straight(3000, 400);
    turn_inplace_by_relative_angle(90, 300);
  }
}