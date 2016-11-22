//
//  init.h
//  robot
//
//  Created by Simone Rossi on 08/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef init_h
#define init_h


#include "include.h"
#include "tacho.h"

engine engines[4];

pthread_t engine_manager_tid;

/**
 *  \details Performs robot initialization (both motors and sensors)
 *  \return 1 if successfull, 0 if errors occured
 */
int
robot_init(void);


int engines_init(void);

void robot_deinit(void);

#endif /* init_h */
