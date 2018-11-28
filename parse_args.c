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
  char *i = malloc(64*sizeof(char));
  // char *i = input;
  strcpy(i,input);
  char **p = malloc(64*sizeof(char*));
  parse_space(i, p);
  // printf("p[0]: %s\n",p[0]);
  // printf("p[1]: %s\n",p[1]);
  // printf("p[2]: %s\n",p[2]);
  if(p[1] && strcmp(p[1], "|") == 0){
    pipes[0] = p[0];
    pipes[1] = p[2];
    // printf("pipes[0]: %s\n",pipes[0]);
    // printf("pipes[1]: %s\n",pipes[1]);
    return 1;
  }else{
    return 0;
  }
}

int parse_args(char * input, char ** parsed, char ** parsed_pipe){
  char ** pipes = malloc(2*sizeof(char*));
  int piped = 0;
  piped = parse_pipe(input, pipes);
  if(piped){
    parsed[0] = pipes[0];
    parsed_pipe[0] = pipes[1];
    // printf("parsed: %s\n",*parsed);
    // printf("parsed_pipe: %s\n",*parsed_pipe);
  }else{
    parse_space(input, parsed);
  }
  // printf("piped: %d\n", piped);
  return 0 + piped;
}
