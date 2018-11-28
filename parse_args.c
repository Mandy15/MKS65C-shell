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
  parsed[i] = NULL;
}

int parse_pipe(char * input, char ** parsed_pipe){
  return 0;
}

int parse_args(char * input, char ** parsed, char ** parsed_pipe){
  int piped = 0;
  parse_space(input, parsed);
  return 0 + piped;
}
