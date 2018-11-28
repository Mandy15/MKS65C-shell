#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"
#define clear() printf("\033[H\033[J")

int exec_builtin(char ** parsed){
  if(strcmp(parsed[0], "exit") == 0){
    clear();
    printf("\n\n\n\n\n\n\n\n\n-----------------------------Leaving Mandy's_Shell------------------------------\n\n");
    sleep(1);
    clear();
    exit(0);
  }else if(strcmp(parsed[0], "cd") == 0){
    chdir(parsed[1]);
    return 1;
  }
  return 0;
}

void exec_cmd(char ** parsed){
  pid_t pid = fork();
  if(pid == -1){
    printf("\nForking failed.\n");
  }else if(pid == 0){
    if(execvp(parsed[0], parsed) < 0){
      printf("\nCommand could not be executed.\n");
    }
    exit(0);
  }else{
    wait(NULL);
  }
}

void exec_pipe(char ** parsed, char ** parsed_pipe){
  int pipefd[2];
  pid_t p1, p2;
  if(pipe(pipefd) < 0) {
    printf("\nPipe could not be initialized");
    return;
  }
  p1 = fork();
  if(p1 < 0) {
    printf("\nCould not fork");
    return;
  }
  if(p1 == 0) {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    if(execvp(parsed[0], parsed) < 0) {
      printf("\nCould not execute command 1..");
      exit(0);
    }
  }else{
    p2 = fork();
    if(p2 < 0) {
      printf("\nCould not fork");
      return;
    }
    if(p2 == 0) {
      close(pipefd[1]);
      dup2(pipefd[0], STDIN_FILENO);
      close(pipefd[0]);
      if(execvp(parsed_pipe[0], parsed_pipe) < 0) {
        printf("\nCould not execute command 2..");
        exit(0);
      }
    }else{
      wait(NULL);
      wait(NULL);
    }
  }
}

void exec_args(int exec_num, char ** parsed, char ** parsed_pipe){
  if(exec_num == 0){
    if(exec_builtin(parsed)){
    }else{
      exec_cmd(parsed);
    }
  }
  if(exec_num == 1){
    exec_pipe(parsed, parsed_pipe);
  }
}
