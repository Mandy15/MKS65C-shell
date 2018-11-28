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

int parse_pipe(char * input, char ** pipes){
  int i;
  for (i = 0; i < 2; i++) {
    pipes[i] = strsep(&input, "|");
    if(pipes[i] == NULL) {
      break;
    }
  }
  if(pipes[1] == NULL) {
    return 0;
  }else{
    return 1;
  }
}

int parse_args(char * input, char ** parsed, char ** parsed_pipe){
  char * pipes[2];
  int piped = 0;
  piped = parse_pipe(input, pipes);
  if(piped){
    parse_space(pipes[0], parsed);
    parse_space(pipes[1], parsed_pipe);
  }else{
    parse_space(input, parsed);
  }
  return 0 + piped;
}
