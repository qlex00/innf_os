#include <stdio.h>
#include <stdlib.h>

int main(){
  int n, *A;

  printf("Skriv inn antall for n: ");
  scanf("%d", &n);
  
  A = (int*) malloc(n * sizeof(int));

  //leser inn n heltall
  int *pektilA = A;
  for(int i = 0; i < n; i++){
    printf("Skriv inn en verdi for n som heltall for tall nr %d: ", i + 1);
    scanf("%d", pektilA);
    pektilA++;
  }

  pektilA = A + (n - 1); //setter peker til siste elemente
  printf("Omvendt rekkefølge:\n");
  for(int i = 0; i < n; i++) {
    printf("%d\n", *pektilA);
    pektilA--; //flytter peker bakover
  }
  
  free(A);
  return 0; 
}

