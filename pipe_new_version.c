#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/**********  déclaration des diverses fonctions utiles au programme ***********/

void parseCmd(char **newTable, char *cmd);
void formatCmd(char **cmd, int maxArg, char **copy);
void StringifyCmd(char **cmd, int lenght, char *cmdString);

/*
  Classe principal du projet
*/

int main(int argc, char *argv[]){

  int fd[2];

  pid_t cpid;

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

    //initialisation du buffer de lecture + lecture du pipe
    char reading_buffer[100];
    while (read(fd[0], reading_buffer, sizeof(reading_buffer)) != 0) {

    }

    close(fd[0]);

    //initialisation du char** contenant les diverses commandes passées au programme
    char *cmd[argc];
    parseCmd(cmd, reading_buffer);

    //exécution des commandes via la fonction execvp
    execvp(cmd[0], cmd);

  }

  //parent process
  else{
    close(fd[0]) ; //close the read end of the pipe

    char message[100] = "";

    StringifyCmd(argv, argc, message);

    write(fd[1], message, strlen(message)+1);

    close(fd[1]);
    exit(EXIT_SUCCESS);
  }
}

//fonction transformant un tableau de string en un long string unique.
void StringifyCmd(char **cmd, int lenght, char *cmdString){

  for (int i = 1; i < lenght-1; i++) {
    strcat(cmdString, cmd[i]);
    strcat(cmdString, " ");
  }
  strcat(cmdString, cmd[lenght-1]);

  printf("pipe envois : %s\n", cmdString);

}

// * fonction transformant un long string unique en un tableau de string.
// * coupe le string au niveau des espaces " "
void parseCmd(char **newTable, char *cmd){

  int incr = 0;

  for (char *table = strtok(cmd, " "); table != NULL; table = strtok(NULL, " ")) {
    newTable[incr] = table;
    incr++;
  }
  newTable[incr] = NULL;

}

/******************************** INUTILE *************************************/

/*  fonction copiant un tableau, en décalant les arguments d'une position, en
*   ignorant le premier argument et en attribuant une valeur NULL au dernier augument
*   de la copie.
*/
void formatCmd(char **cmd, int maxArg, char **copy){

  for (int i = 0; i < maxArg-1; i++) {
    copy[i] = cmd[i+1];
  }

  copy[maxArg-1] = NULL;
}
