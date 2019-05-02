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
  char message[] = "manges mes nouilles";

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
    read(fd[0], &reading_buffer, 100);
    printf("%s\n", reading_buffer);
    close(fd[0]);
    _exit(EXIT_SUCCESS);
  }

  //parent process
  else{
    close(fd[0]) ; //close the write end of the pipe
    write(fd[1], message, sizeof(message));
    close(fd[1]);
    exit(EXIT_SUCCESS);
  }
}
