#include <iostream>
using namespace std;


#define NUM 10

int main(int argc, char *argv[]) {
  cout << "arguments counts : " << argc << endl;
  for (int i = 0; i < argc; ++i) {
    cout << "arg " << i << " is: " << argv[i] << endl;
  }
  return 0;
}
