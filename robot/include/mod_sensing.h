//
//  mod_sensing.h
//  Module Sensing header file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 13/11/16.
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#ifndef MJOLNIR_MOD_SEN_H
#define MJOLNIR_MOD_SEN_H

#include <mjolnir.h>

/ **
  * FUNCTION DECLERATIONS
  */

/* Obstacles detection */
void mod_sen_obstacles_detection(void);

/* Ball detection */
void mod_sen_ball_detection(void);

/* Ball area detection */
void mod_sen_ball_area_detection(void);

/* Destination detection */
void mod_sen_dest_detection(void);

/* Borders detection */
void mod_sen_borders_detection(void);

#endif /* MJOLNIR_MOD_SEN_H */
