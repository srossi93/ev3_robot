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
  if (us->distance < threashold)
    return 1;
  else
    return 0;
  
}