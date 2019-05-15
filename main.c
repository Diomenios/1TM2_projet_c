#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
*                                                                             *
*         AUTHORS : Louis Arys, Matthew Everard, François Charlier            *                                                                 *
*                                                                             *
*******************************************************************************/
int main(int argc, char *argv[]){

  int fd[2];

  pid_t cpid;

  if (pipe(fd) == -1) {
    //pipe initialisation + management of the possible errors
    perror("pipe");
    exit(EXIT_FAILURE); //or exit(1)
  }

  //fork execution + management of the possible errors
  cpid = fork();

  if(cpid == -1){
    perror("fork");
    exit(EXIT_FAILURE);
  }

  //child process
  if (cpid == 0) {
    close(fd[0]) ; //close the read end of the pipe

    /*
    * Put the write end of the pipe at the standart output
    * Put the write end of the pipe at the standart error output
    */
    dup2(fd[1], 1);
    dup2(fd[1], 2);

    close(fd[1]); //close the write end o the pipe

    execvp(argv[1], &argv[1]); // execute the command pass in argument

  }

  //parent process
  else{

    close(fd[1]) ; //close the read end of the pipe

    char reading_buffer[20]=""; //declaration of reading buffer

    /*
    * Read the pipe while data is write inside
    * Write the data read in the stdout of the father process
    */
    while (read(fd[0], reading_buffer, sizeof(reading_buffer)) !=0) {
      write(1, reading_buffer, sizeof(reading_buffer));
    }


    close(fd[0]);  //close the reading end of the pipe

    exit(EXIT_SUCCESS); //exit the program with true output
  }
}
