#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main() {
  char file1[256], file2[256];
  struct stat stat1, stat2;

  printf("Please input two valid file names: ");
  scanf("%255s, %255s", file1, file2);

  /*if (stat(file1, &stat1) == -1) {
    perror("Error accessing the first file");
    return 1;
  }

  if (stat(file2, &stat2) == -1) {
    perror("Error accesing the second file");
    return 1;
  }*/
  
  printf("\n%s -> I-node:%ld Links:%ld Size:%ld\n",
	 file1, (long)stat1.st_ino, (long)stat1.st_nlink, (long)stat1.st_size);
  printf("%s -> I-node:%ld Links:%ld Size:%ld\n",
	 file2, (long)stat2.st_ino, (long)stat2.st_nlink, (long)stat2.st_size);

  if (stat1.st_ino == stat2.st_ino && stat1.st_dev == stat2.st_dev) {
    printf("\nThe two files are identical\n");
  } else {
    printf("\nThe two files are not identical\n");
  }

  return 0;
}
