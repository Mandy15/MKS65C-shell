#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"

int main(){
  char line[100] = "ls -l --all --color";
  char *s1 = line;
  char ** args = read_line( s1 );
  return 0;
}
