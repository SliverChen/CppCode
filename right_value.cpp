#include <iostream>
using namespace std;


void process_value(int &i) { cout << "LValue processed: " << i << endl; }


void process_value(int &&i) { cout << "RValue processed: " << i << endl; }

void forward_value(int &&i) {
  process_value(i);
}

int main() {
  int a = 0;
  process_value(a);
  process_value(1);
  forward_value(2);
  return 0;
}
