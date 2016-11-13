//
//  mod_geoloc.h
//  Module Geolocation header file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 13/11/16.
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#ifndef MJOLNIR_MOD_GEO_H
#define MJOLNIR_MOD_GEO_H

#include <mjolnir.h>

/ **
  * FUNCTION DECLERATIONS
  */

/* Get current location on x,y axis */
void mod_geo_get_location(int32_t *x, int32_t *y);

/* Logging position */
void mod_geo_logging(int32_t x, int32_t y);

/* Set interval time for logging position */
void mod_geo_set_interval_log(uint32_t time);

#endif /* MJOLNIR_MOD_GEO_H */
