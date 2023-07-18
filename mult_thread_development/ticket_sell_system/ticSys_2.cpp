/*
    ticket sell system
        --- mutex
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// global var
int tickets = 1000;

// create a mutex
pthread_mutex_t mutex;

void *sellticket(void *arg) {
  // sell tickets
  while (1) {

    // add mutex
    pthread_mutex_lock(&mutex);

    if (tickets > 0) {
      usleep(6000);
      printf("%ld is buying NO.%d ticket.\n", pthread_self(), tickets);
      --tickets;
    } else {
      pthread_mutex_unlock(&mutex);
    }

    // unlock the mutex
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

int main() {
  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, sellticket, NULL);
  pthread_create(&tid2, NULL, sellticket, NULL);
  pthread_create(&tid3, NULL, sellticket, NULL);

  // recover the resources of child threads, start blocking
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

  pthread_exit(NULL);

  // release mutex
  pthread_mutex_destroy(&mutex);

  return 0;
}
