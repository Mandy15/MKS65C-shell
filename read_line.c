#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"

int read_line(char * str){
  printf(">>> ");
  char *buf;
  fgets(buf, 15, stdin);
  if(strlen(buf) != 0){
    str = buf;
    return 0;
  }else{
    return 1;
  }
}
