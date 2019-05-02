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

  char buf;

  //initialisation du pipe + gestion des possible erreurs
  if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE); //or exit(1)
    }
  cpid = fork();
  if(cpid == -1){
  perror("fork");
  exit(EXIT_FAILURE);
  }

  //child process
  if (cpid == 0) {
    printf("Je suis ton fils\n");
  }
  //parent process
  else{
    printf("je suis ton père\n");
  }
}
