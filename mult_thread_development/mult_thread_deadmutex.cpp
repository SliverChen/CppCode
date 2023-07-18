#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


// create two mutex
pthread_mutex_t mtx1, mtx2;

void *workA(void *arg) {
  pthread_mutex_lock(&mtx1);
  sleep(1);
  pthread_mutex_lock(&mtx2);

  printf("workA...\n");

  pthread_mutex_unlock(&mtx2);
  pthread_mutex_unlock(&mtx1);
  return NULL;
}

void *workB(void *arg) {
  pthread_mutex_lock(&mtx2);
  sleep(1);
  pthread_mutex_lock(&mtx1);

  printf("workB..\n");

  pthread_mutex_unlock(&mtx1);
  pthread_mutex_unlock(&mtx2);

  return NULL;
}

int main() {

  // initialize mutex
  pthread_mutex_init(&mtx1, NULL);
  pthread_mutex_init(&mtx2, NULL);

  // create two child threads
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, workA, NULL);
  pthread_create(&tid2, NULL, workB, NULL);

  // recover the child thread resource
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  // release mutex resource
  pthread_mutex_destroy(&mtx1);
  pthread_mutex_destroy(&mtx2);

  return 0;
}


