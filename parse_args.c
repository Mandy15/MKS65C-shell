#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"

void parse_space(char * input, char ** parsed){
  char * p = input;
  int i;
  for(i = 0; p; i++ ){
    parsed[i] = strsep( &p, " " );
  }
  // parsed[i-1] = strsep( &parsed[i-1], "NULL" );
  parsed[i] = NULL;
  // printf("parsed[0]: %s", parsed[1]);
}

int parse_pipe(char * input, char ** parsed_pipe){
  return 0;
}

int parse_args(char * input, char ** parsed, char ** parsed_pipe){
  parse_space(input, parsed);
  return 1;
}
