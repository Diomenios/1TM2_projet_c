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

    read(fd[0], &reading_buffer, 100);

    printf("j'ai lu : %s\n", reading_buffer);

    close(fd[0]);

    //write in the Console Line the message
    printf("%s %s\n", "the buffer contains : " ,reading_buffer);

    char *childTable[argc][20];
    int incr = 0;
    for (char *table = strtok(reading_buffer, " "); table != NULL; table = strtok(NULL, " ")) {
      *childTable[incr] = table;
      incr++;
      printf("tour de clivage : %d\n", incr);
    }

    printf("argc = %d\n", argc);

    *childTable[argc-1] = NULL;

    for (int i = 0; i < argc-1 ; i++) {
      printf("%d :%s\n", i+1 ,*childTable[i]);
    }

    execvp(*childTable[0], *childTable);
  }

  //parent process
  else{
    close(fd[0]) ; //close the read end of the pipe

    char message[100] = "";
    int lenght = 0;

    for (int i = 1; i < argc-1; i++) {
      strcat(message, argv[i]);
      strcat(message, " ");

      lenght+= sizeof(argv[i]) + 1;

    }
    strcat(message, argv[argc-1]);
    lenght+= sizeof(argv[argc-1]);

    //write the pipe and save the information into reading_buffer
    write(fd[1], message, lenght);

    close(fd[1]);
    exit(EXIT_SUCCESS);
  }
}
