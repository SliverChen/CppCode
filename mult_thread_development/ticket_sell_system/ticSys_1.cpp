/*
    ticket sell system
        --- thread sync
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int tickets = 100;

void *sellticket(void *arg) {
  // sell ticket
  while (tickets > 0) {
    // The same thread must run the following codes,
    // or another thread can not seize
    usleep(6000);
    printf("%ld selling NO.%d ticket\n", pthread_self(), tickets);
    tickets--;
  }
  return NULL;
}

int main() {
  // create three child threads
  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, sellticket, NULL);
  pthread_create(&tid2, NULL, sellticket, NULL);
  pthread_create(&tid3, NULL, sellticket, NULL);

  // recover the resource of child threads, start blocking
//   pthread_join(tid1, NULL);
//   pthread_join(tid2, NULL);
//   pthread_join(tid3, NULL);

  // set threads detach
  pthread_detach(tid1);
  pthread_detach(tid2);
  pthread_detach(tid3);

  pthread_exit(NULL);
  return 0;
}
