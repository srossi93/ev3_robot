//
//  utilities.c
//  robot
//
//

#include "utilities.h"

extern char msg[255];

void
log_to_file(char *msg)
{
  FILE *file_ptr = fopen("log.txt", "a");
  fprintf(file_ptr, "%s", msg);
  
#ifdef DEBUG_TERMINAL
  printf("%s", msg);
#endif
  
  fclose(file_ptr);
}


int
identify_engines(engine_ptr *right_engine, engine_ptr *left_engine)
{
  int max_speed = 0;
  uint8_t gyro_sensor_id;
  uint8_t engine1, engine2;
  int32_t initial_absolute_angle = 0;
  int32_t final_absolute_angle = 0;
  
  sprintf(msg, "*** Start engine identification ***\n");
  log_to_file(msg);
  
  // Search the first engine
  if ( !ev3_search_tacho(LEGO_EV3_L_MOTOR, &engine1, 0) )
  {
    sprintf(msg, " --> No LEGO_EV3_L_MOTOR found\n\tAborting...\n");
    log_to_file(msg);
    return 0;
  }
  
  // Search the second engine
  if (! ev3_search_tacho(LEGO_EV3_L_MOTOR, &engine2, engine1+1) )
  {
    sprintf(msg, " --> No second LEGO_EV3_L_MOTOR found\n\tAborting...\n");
    log_to_file(msg);
    return 0;
  }
  
  // Search the gyroscope
  if( !ev3_search_sensor(LEGO_EV3_GYRO, &gyro_sensor_id, 0) )
  {
    sprintf(msg, " --> No LEGO_EV3_GYRO found\n\tAborting...\n");
    log_to_file(msg);
    return 0;
  }

  get_sensor_value(0, gyro_sensor_id, &initial_absolute_angle);
  sprintf(msg, "[GYRO] : Initial absolute value %d\n", initial_absolute_angle);
  log_to_file(msg);
  
  get_tacho_max_speed( engine1, &max_speed );
  set_tacho_speed_sp( engine1, max_speed / 16 );
  set_tacho_ramp_up_sp( engine1, 0 );
  set_tacho_ramp_down_sp( engine1, 0 );
  set_tacho_position_sp( engine1, 180 );
  set_tacho_command_inx( engine1, TACHO_RUN_TO_REL_POS );
  
  sleep(50*1000);
  get_sensor_value(0, gyro_sensor_id, &final_absolute_angle);
  
  sprintf(msg, "[GYRO] : Final absolute value %d\n", final_absolute_angle);
  log_to_file(msg);
  
  set_tacho_position_sp( engine1, -180 );
  set_tacho_command_inx( engine1, TACHO_RUN_TO_REL_POS );
  
  usleep(5000*1000);
  get_sensor_value(0, gyro_sensor_id, &initial_absolute_angle);
  
  sprintf(msg, "[GYRO] : Restart absolute value %d\n", initial_absolute_angle);
  log_to_file(msg);
  
  if ((final_absolute_angle - initial_absolute_angle) < 0)
  {
    *right_engine = engine1;
    *left_engine = engine2;
  }
  else
  {
    *right_engine = engine2;
    *left_engine = engine1;
  }
  
  return 1;
  
}