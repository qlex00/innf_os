#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
   
#define MAX_WAIT 2000000

pthread_mutex_t mutex;
pthread_cond_t cond;
int antall_blokkert = 0;

void *terningkast(void *nr)
{
   while(1)
   {
      int terning = rand() % 6 + 1;
      
      pthread_mutex_lock(&mutex);

      printf("Tråd %3ld -> %d\n", (long) nr, terning);

      if (terning == 1){
	antall_blokkert++;
	printf("Tråd %3ld blokkerer. Antall tråder blokkert: %d\n", (long)nr, antall_blokkert);
	pthread_cond_wait(&cond, &mutex);
	antall_blokkert--;
	printf("Tråd %3ld vekket. Antall tråder blokkert: %d\n", (long)nr, antall_blokkert);
      }
      else if (terning == 6) {
	printf("Tråd %3ld fikk 6 og vekker en annen tråd. Antall tråder blokkert: %d\n", (long)nr, antall_blokkert);
	pthread_cond_signal(&cond);
      }

      pthread_mutex_unlock(&mutex);
      
      usleep(rand() % MAX_WAIT + 1);
   }
}

int main()
{
   int n;
   long i;
   pthread_t t[100];

   printf("n? ");
   scanf("%d", &n);
   
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&cond, NULL);
   
   for (i = 0; i < n; i++) {
     pthread_create(&t[i], NULL, terningkast, (void *) i);
   }
   
   for (i = 0; i < n; i++) {
       pthread_join(t[i], NULL);
   }

   pthread_mutex_destroy(&mutex);
   pthread_cond_destroy(&cond);
   
   return 0;
}
