//
//  obstacle_detection.c
//  robot
//
//  Created by Simone Rossi on 10/01/17.
//  Copyright © 2017 Simone Rossi. All rights reserved.
//

#include <stdio.h>
#include "globals.h"


int
obstacle_detected(int threashold){
  //int sum = 0;
  //int i;
  //for (i = 0; i < 3; i++)
  //{
    //sum += us->distance;
    //msleep(100);
  //}
  //if (sum/3 < threashold)
    //return 1;
  //else
    //return 0;
  
  
  
  if (us->distance <= threashold){
    printf("OBSTACLE at %d\n", us->distance);
    return 1;
  }
  else
    return 0;
  
}