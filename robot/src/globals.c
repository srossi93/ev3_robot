//
//  globals.c
//  robot
//
//  Created by Simone Rossi on 12/01/17.
//  Copyright © 2017 Simone Rossi. All rights reserved.
//

#include <stdio.h>
#include "globals.h"

ARM_STATUS arm_status;

ROBOT_STATUS robot_status = ROBOT_NOT_RUNNING;

POSITION robot_position = {0,0,0};
