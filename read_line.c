#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "shell.h"

char ** read_line( char * line ) {
  char ** cmds = (char **) malloc(10 * sizeof(char *));
  char * p = line;
  int i;
  for (i = 0; p; i++ ) {
    cmds[i] = strsep( &p, " " );
    printf("[%s]\n", cmds[i]);
  }
  cmds[i] = NULL;
  return cmds;
}
