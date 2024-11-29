#include <stdio.h>
#include <pthread.h>

int count = 0; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increase()
{ 
   int i; 
   for(i = 0; i < 1e8; ++i) {
      pthread_mutex_lock(&mutex);
      count++;
      pthread_mutex_unlock(&mutex);
   }
   return NULL;
}

void *decrease()
{  
   int i;
   for(i = 0; i < 1e8; ++i) {
      pthread_mutex_lock(&mutex);
      count--;
      pthread_mutex_unlock(&mutex);
   }
   return NULL;
}

int main()
{ 
   pthread_t thread1, thread2; 

   pthread_create(&thread1, NULL, increase, NULL);
   pthread_create(&thread2, NULL, decrease, NULL);
   
   pthread_join(thread1, NULL); 
   pthread_join(thread2, NULL); 
  
   printf("count = %d\n", count);

   pthread_mutex_destroy(&mutex);
   return 0;
}
