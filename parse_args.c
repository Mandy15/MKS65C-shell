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

// Takes input from user and parses it by separating args by spaces.
// The modified input is then put into an array. No return.
void parse_space(char * input, char ** parsed){
  char * p = input;
  int i;
  for(i = 0; p; i++ ){
    parsed[i] = strsep( &p, " " );
  }
  parsed[i] = NULL;
}

// Takes input from user and checks for simple pipe (returning the corresponding int).
// Parses input and separates the pgrms used in the pipe into an array. Returns 0 if false, 1 if true.
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

// Takes input from user and checks for simple redirection (returning the corresponding int).
// Parses input and separates the command and file used in the redirection into an array. Returns 0 if false, 2 if true.
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

// Takes input from user and checks for separated commands on one line with semicolons.
// Parses input and separates the commands in an array. Returns 0 if false, 3 if true.
int parse_semi(char * input, char ** pipes){
  char *i = malloc(64*sizeof(char));
  strcpy(i,input);
  char **p = malloc(64*sizeof(char*));
  parse_space(i, p);
  if(p[1] && strcmp(p[1], ";") == 0){
    pipes[0] = p[0];
    pipes[1] = p[2];
    return 3;
  }else{
    return 0;
  }
}

// Takes in input and two empty arrays for use depending on parse.
// Correctly parses the input according to whether it has pipe/redirection/semicolons or not.
// Returns a corresponding int to what parse was used.
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
      piped = parse_semi(input, pipes);
      if(piped){
        parsed[0] = pipes[0];
        parsed_pipe[0] = pipes[1];
      }else{
        parse_space(input, parsed);
      }
    }
  }
  return 0 + piped;
}
//
