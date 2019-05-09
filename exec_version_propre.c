#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


void parseCmd(char **newTable, char *cmd);
void formatCmd(char **cmd, int maxArg, char **copy);
/*
  Classe principal du projet
*/

int main(int argc, char *argv[]){

  char *buf[argc];

  formatCmd(argv, argc, buf);

  execvp(buf[0], buf);
}

void parseCmd(char **newTable, char *cmd){

  int incr = 0;
  for (char *table = strtok(cmd, " "); table != NULL; table = strtok(NULL, " ")) {
    newTable[incr] = table;
    incr++;
    printf("tour de clivage : %d\n", incr);
  }
}

void formatCmd(char **cmd, int maxArg, char **copy){

  for (int i = 0; i < maxArg-1; i++) {
    copy[i] = cmd[i+1];
  }

  copy[maxArg-1] = NULL;
}
