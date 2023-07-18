/*
    deliver the parameter to thread
*/

#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;


struct thread_data {
  int thread_id;
  char *mes;
};

void *printHello(void *arg) {
  struct thread_data *my_data;

  my_data = (struct thread_data *)arg;

  cout << "Thread_id: " << my_data->thread_id << endl;
  cout << "Message: " << my_data->mes << endl;

  pthread_exit(NULL);
}

int main() {
  pthread_t threads[5];
  struct thread_data td[5];
  int rc, i;

  for (i = 0; i < 5; ++i) {
    cout << "main(): creating thread, " << i << endl;
    td[i].thread_id = i;
    td[i].mes = (char *)"This is message.";
    rc = pthread_create(&threads[i], NULL, printHello, (void *)&td[i]);

    if (rc) {
      cout << "Error: unable to create thread, " << rc << endl;
      exit(-1);
    }
  }
  pthread_exit(NULL);
}
