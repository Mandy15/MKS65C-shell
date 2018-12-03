#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
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
  strcpy(i,input);
  char **p = malloc(64*sizeof(char*));
  parse_space(i, p);
  if(p[1] && strcmp(p[1], "|") == 0){
    pipes[0] = p[0];
    pipes[1] = p[2];
    return 1;
  }else{
    return 0;
  }
}

int parse_redirect(char * input, char ** pipes){
  char *i = malloc(64*sizeof(char));
  strcpy(i,input);
  char **p = malloc(64*sizeof(char*));
  parse_space(i, p);
  if(p[1] && strcmp(p[1], ">") == 0){
    pipes[0] = p[0];
    pipes[1] = p[2];
    return 2;
  }else if (p[1] && strcmp(p[1], "<") == 0){
    pipes[0] = p[2];
    pipes[1] = p[0];
    return 2;
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
  }else{
    piped = parse_redirect(input, pipes);
    if(piped){
      parsed[0] = pipes[0];
      parsed_pipe[0] = pipes[1];
    }else{
      parse_space(input, parsed);
    }
  }
  return 0 + piped;
}
