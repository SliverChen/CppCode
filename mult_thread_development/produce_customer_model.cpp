#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// create a mutex
pthread_mutex_t mutex;

struct Node {
  int num;
  struct Node *next;
};

// head node
struct Node *head = NULL;

void *producer(void *arg) {
  // insert to head, delete on head

  while (1) {
    pthread_mutex_lock(&mutex);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->next = head;
    head = newNode;

    newNode->num = rand() % 1000;
    printf("add node, num : %d, tid: %ld\n", newNode->num, pthread_self());

    pthread_mutex_unlock(&mutex);
    usleep(100);
  }
  return NULL;
}

void *customer(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);

    // the pointer of saving head node
    struct Node *tmp = head;

    // judge if it has data
    if (head != NULL) {
      head = head->next;
      printf("del node, num : %d, tid: %ld\n", tmp->num, pthread_self());
      free(tmp);

      pthread_mutex_unlock(&mutex);
      usleep(100);
    }
    else {
    pthread_mutex_unlock(&mutex);
    }
  }
  return NULL;
}

int main() {

  pthread_mutex_init(&mutex, NULL);

  // create five producer threads and five customer threads
  pthread_t ptids[5], ctids[5];

  for (int i = 0; i < 5; ++i) {
    pthread_create(&ptids[i], NULL, producer, NULL);
    pthread_create(&ctids[i], NULL, customer, NULL);
  }

  for (int i = 0; i < 5; ++i) {
    pthread_detach(ptids[i]);
    pthread_detach(ctids[i]);
  }

  while (1) {
    sleep(10);
  }

  pthread_mutex_destroy(&mutex);

  pthread_exit(NULL);

  return 0;
}
