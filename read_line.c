#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"

char * read_line(){
  printf(">>> ");
  char *buf = malloc(64*sizeof(char));
  fgets(buf, 64, stdin);
  if(strlen(buf) != 0){
    int len = strlen(buf);
    if(buf[len-1] == '\n'){
      buf[len-1] = '\0';
    }
    return buf;
  }else{
    return NULL;
  }
}
