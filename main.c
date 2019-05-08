#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/*
  Classe principal du projet
*/

int main(int argc, char *argv[]){

  int fd[2];

  pid_t cpid;
  char reading_buffer[100];
  char buf;

  //initialisation du pipe + gestion des possible erreurs
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE); //or exit(1)
  }

  //execution du fork + gestion des possibles erreurs
  cpid = fork();

  if(cpid == -1){
    perror("fork");
    exit(EXIT_FAILURE);
  }

  //child process
  if (cpid == 0) {
    close(fd[1]) ; //close the write end of the pipe

    for (int i = 1; i < argc; i++) {
       //read the pipe and save the information into reading_buffer
       read(fd[0], &reading_buffer, 10);
       printf("%s\n", reading_buffer);
    }

    //write in the Console Line the message
    printf("%s %s\n", "the buffer contains : " ,reading_buffer);

    char *childTable[argc-1][20];
    int incr = 0;
    for (char *table = strtok(reading_buffer, " "); table != NULL; table = strtok(NULL, " ")) {
      *childTable[incr] = table;
      incr++;
    }
    close(fd[0]);

    execvp(*childTable[0], *childTable);
  }

  //parent process
  else{
    close(fd[0]) ; //close the read end of the pipe

    for (int i = 1; i < argc; i++) {
       //write the pipe and save the information into reading_buffer
       write(fd[1], argv[i], sizeof(argv[i]));
    }
    close(fd[1]);
    exit(EXIT_SUCCESS);
  }
}
