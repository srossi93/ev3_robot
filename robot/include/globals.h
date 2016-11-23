//
//  globals.h
//  robot
//
//  Created by Simone Rossi on 23/11/16.
//  Copyright © 2016 Simone Rossi. All rights reserved.
//

#ifndef globals_h
#define globals_h

#include "tacho.h"

engine engines[4];

pthread_t engine_manager_tid;

sem_t sem_right_engine, sem_left_engine;

#endif /* globals_h */
