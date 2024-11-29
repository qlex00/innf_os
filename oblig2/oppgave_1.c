#include <stdio.h>

int main() {

  int S = 0;
  
  for (int n = 0; n <= 100; n++) {
      S += n * n;
  }

  printf("Sum er: %d\n", S);

  return 0;
}
