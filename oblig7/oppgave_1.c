#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FIFO_PATH "/tmp/myfifo"

void writer()
{
   int fd;
   char message[] = "Music from Big Pink!";

   fd = open(FIFO_PATH, O_WRONLY);
   write(fd, message, strlen(message) + 1);
   printf("Message sent    : %s\n", message);
   close(fd);
}

void reader()
{
   int fd;
   char buffer[100];

   fd = open(FIFO_PATH, O_RDONLY);
   read(fd, buffer, sizeof(buffer));
   printf("Message received: %s\n", buffer);
   close(fd);
}

int main()
{
   pid_t pid;

   mkfifo(FIFO_PATH, 0666);

   pid = fork();

   if (pid == 0)
   {
      writer();
   }
   else
   {
      reader();
      wait(NULL);
      unlink(FIFO_PATH);
   }
}
