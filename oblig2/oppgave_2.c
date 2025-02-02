#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_STR 1000
#define MAX_VERDI 100000

int main() {
  int num[ARRAY_STR];
  int min_verdi, max_verdi;

   srand(time(NULL));

   for (int i = 0; i < ARRAY_STR; i++) {
     num[i] = rand() % MAX_VERDI; 
   }

   min_verdi = max_verdi = num[0];

   for (int i = 1; i < ARRAY_STR; i++) {
     if(num[i] < min_verdi) {
       min_verdi = num[i];
     }
     if (num[i] > max_verdi){
       max_verdi = num[i];
     }
   }

   printf("min verdi: %d\n", min_verdi);
   printf("max verdi: %d\n", max_verdi);

   return 0;
}
