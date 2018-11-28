#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"
#define clear() printf("\033[H\033[J")

void start(){
  clear();
  printf("----------------------------Welcome to Mandy's_Shell---------------------------\n");
}

void print_dir(){
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("\n%s", cwd);
}

int main(){
  char *input = malloc(64*sizeof(char));
  char **parsed = malloc(64*sizeof(char*));
  char **parsed_pipe = malloc(64*sizeof(char*));
  int exec_num = 0;
  start();
  while(1){
    print_dir();
    // if(read_line(input)){
    //   continue;
    // }
    input = read_line();
    exec_num = parse_args(input, parsed, parsed_pipe);
    exec_args(exec_num, parsed, parsed_pipe);
    // printf("---------------------------Leaving Mandy's_Shell---------------------------\n");
  }
  return 0;
}
