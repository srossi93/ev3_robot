//
//  utilities.c
//  robot
//
//

#include "utilities.h"

extern char msg[255];

char *time_stamp(){
  
  char *timestamp = (char *)malloc(sizeof(char) * 21);
  time_t ltime;
  ltime=time(NULL);
  struct tm *tm;
  tm=localtime(&ltime);
  
  sprintf(timestamp,"%04d-%02d-%02d %02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon,
          tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
  return timestamp;
}


void
log_to_file(char *msg)
{
  FILE *file_ptr = fopen("log.txt", "a");
  char msg_to_file[255];
  
  sprintf(msg_to_file, "%s : %s", time_stamp(), msg);
  fprintf(file_ptr, "%s", msg_to_file);
  
#ifdef DEBUG_TERMINAL
  printf("%s", msg);
#endif
  
  fclose(file_ptr);
}

