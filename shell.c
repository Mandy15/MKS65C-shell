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

// No args/returns. Clears terminal for shell.
void start(){
  clear();
  printf("\n\n\n\n\n\n\n\n\n----------------------------Welcome to Mandy's_Shell---------------------------\n");
  sleep(1);
  clear();
}

// No args/returns. Prints the current directory to mimic bash shell.
void print_dir(){
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("\n%s", cwd);
}

// No args. Runs shell. Returns 0.
int main(){
  char *input = malloc(64*sizeof(char));
  char **parsed = malloc(64*sizeof(char*));
  char **parsed_pipe = malloc(64*sizeof(char*));
  int exec_num = 0;
  start();
  while(1){
    print_dir();
    input = read_line();
    exec_num = parse_args(input, parsed, parsed_pipe);
    exec_args(exec_num, parsed, parsed_pipe);
  }
  return 0;
}
//
