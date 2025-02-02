#include <stdio.h>
#include <stdlib.h>

long fib(int n) {
    if(n == 0) return 0;
    if(n == 1) return 1;

    long a = 0, b = 1, sum;

    for(int i = 2; i <= n; i++) {
       sum = a + b;
       a = b;
       b = sum;
    }
    return b;
}

int main() {
    int n;
    FILE *file;

    printf("Gi n, en verdi: ");
    scanf("%d", &n);

    file = fopen("fibonacci.txt", "w");
    if (file == NULL) {
      printf("Finner ikke filen du prøver å åpne.\n");
      return 1;
    }

    for (int i = 0; i <= n; i++) {
	fprintf(file, "F%d = %ld\n", i, fib(i));
    }

    fclose(file);

    printf("F0 til F%d er lagret i fibonacci.txt.\n", n);
    return 0;
}
