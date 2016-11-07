//
//  movement.c
//  robot
//
//

#include "movement.h"

void
turn_by_relative_angle(uint16_t angle)
{
  uint8_t gyro_sensor_id;
  uint8_t right_motor_id;
  uint8_t left_motor_id;
  int32_t initial_absolute_angle = 0;
  
  if( !ev3_search_sensor(LEGO_EV3_GYRO, &gyro_sensor_id, 0))
  {
    printf("Gyro sensor not found...\n");
    return;
  }
  
  get_sensor_value(0, gyro_sensor_id, &initial_absolute_angle);
  printf("[GYRO] : Initial absolute value %d\n", initial_absolute_angle);
  
}