#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/*
  example of an execvp() program and test of strtok() function.
  The strtok() function maintains a static pointer to your previous passed string
  => so for obtain the next "token", you have to execute the code : reference = strtok(NULL, selector)

  WHERE :
    - selector is a caracter or a group of caracters that you have use to splite The
      initial string.
    - reference is a char * .
*/


//Principal function of the test program
int main(int argc, char *argv[]){

/******************** creation of a pseudo-pipe output ************************/
char chaine[100] = "";

//put the string inside the buffer
for (int i = 1; i < argc ; i++) {
  strcat(chaine, argv[i]);
  strcat(chaine, " ");
}

//use the strtok() function to split in pieces the string for create array of string
char *finalTable[argc-1][20];
int id = 0;

for (char *table = strtok(chaine, " "); table != NULL; table = strtok(NULL, " ")) {
  *finalTable[id] = table;
  id++;
}

//check that the table is rigth created
for (int i = 0; i < argc-1 ; i++) {
  printf("%s\n", *finalTable[i]);
}

//use of execvp
execvp(*finalTable[0], *finalTable);
}
