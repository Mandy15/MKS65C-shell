#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"

void exec_cmd(char ** parsed){
  pid_t pid = fork();
  if(pid == -1){
    printf("\nForking failed.\n");
    return;
  }else if(pid == 0){
    if(execvp(parsed[0], parsed) < 0){
      printf("\nCommand could not be executed.\n");
    }
    exit(0);
  }else{
    wait(NULL);
    return;
  }
}

void exec_pipe(char ** parsed_pipe){
  ;
}

void exec_args(int exec_num, char ** parsed, char ** parsed_pipe){
  if(exec_num == 1){
    exec_cmd(parsed);
  }
  if(exec_num == 2){
    exec_pipe(parsed_pipe);
  }
}
