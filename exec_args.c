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
#define clear() printf("\033[H\033[J")

// Checks for built-in commands (cd or exit) and executes it if present.
// Returns 0 if no built-in commands or exited shell. Returns 1 for cd.
int exec_builtin(char ** parsed){
  if(strcmp(parsed[0], "exit") == 0){
    // clear();
    printf("\n\n\n\n\n\n\n\n\n-----------------------------Leaving Mandy's_Shell------------------------------\n\n");
    sleep(1);
    // clear();
    exit(0);
  }else if(strcmp(parsed[0], "cd") == 0){
    chdir(parsed[1]);
    return 1;
  }
  return 0;
}

// Takes in array of command and args, then forks and executes commands. No returns.
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

// Executes simple pipe with programs separated into two arrays. No returns.
void exec_pipe(char ** parsed, char ** parsed_pipe){
  FILE *pipein_fp, *pipeout_fp;
  char readbuf[80];
  if (( pipein_fp = popen(parsed[0], "r")) == NULL){
    perror("popen");
    exit(1);
  }
  if (( pipeout_fp = popen(parsed_pipe[0], "w")) == NULL){
    perror("popen");
    exit(1);
  }
  while(fgets(readbuf, 80, pipein_fp)){
    fputs(readbuf, pipeout_fp);
  }
  pclose(pipein_fp);
  pclose(pipeout_fp);
}

// Executes simple redirection with commands and files into two arrays. No returns.
void exec_redirect(char ** parsed, char ** parsed_pipe){
  pid_t pid = fork();
  if(pid == -1){
    printf("\nForking failed.\n");
  }else if(pid == 0){
    int in, out;
    in = open(parsed[0], O_RDONLY);
    out = open(parsed_pipe[0], O_WRONLY | O_TRUNC | O_CREAT);
    dup2(in, 0);
    dup2(out, 1);
    close(in);
    close(out);
    if(execvp(parsed[0], parsed) < 0){
      printf("\nCommand could not be executed.\n");
    }
    exit(0);
  }else{
    wait(NULL);
  }
}

// Executes multiple commands that were separated with ; in two arrays. No returns.
void exec_semi(char ** parsed, char ** parsed_pipe){
  pid_t pid = fork();
  if(pid == -1){
    printf("\nForking failed.\n");
  }else if(pid == 0){
    exec_cmd(parsed);
    exit(0);
  }else{
    exec_cmd(parsed_pipe);
    wait(NULL);
  }
}

// Uses the correct function based on exec_num from parsing to
// execute built-in cmds/pipes/redirection and passes the needed arrays. No returns.
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
  if(exec_num == 2){
    exec_redirect(parsed, parsed_pipe);
  }
  if(exec_num == 3){
    exec_semi(parsed, parsed_pipe);
  }
}
//
