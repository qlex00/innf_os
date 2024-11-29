#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

void sig_handler(int sig){
  if (sig == SIGUSR1){
    printf("Slutt å masse, din lille sa**n.");
  }
}

int main() {
  pid_t child = fork();

  if(child == 0) {

    char input[100];

    while(1) {
        printf("Skriv en streng ('quit' for å avslutte): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if(strcmp(input, "quit") == 0){
            exit(0);
        }
        else {
              kill(getppid(), SIGUSR1);
              usleep(200000);
        }
    }

  } else {
    wait(NULL);
    signal(SIGUSR1,sig_handler);
  }
  return 0;
}


