#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
using namespace std;


int main() {
  pid_t pid;
  char *msg;
  int k;

  pid = fork();
  switch (pid) {
  case 0:
    msg = (char *)"Child process is running\n";
    k = 3;
    break;
  case -1:
    perror("Process creation failed\n");
    break;
  default:
    msg = (char *)"Parent process is running\n";
    k = 5;
    break;
  }

  while (k > 0) {
    puts(msg);
    sleep(1);
    k--;
    }
}
