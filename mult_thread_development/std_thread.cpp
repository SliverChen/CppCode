#include <iostream>
#include <thread>

using namespace std;


//a virtual function
void foo(int z) {
  for (int i = 0; i < z; ++i) {
    cout << "thread is using function point as parameter\n";
    }
}

// object can be called
class thread_obj {
public:
  void operator()(int x) {
    for (int i = 0; i < x; ++i) {
      cout << "thread is using function object as parameter\n";
      }
  }
  
};


int main() {
  cout << "thread 1,2,3 run itself.\n";

  // function point
  thread th1(foo, 3);

  // function object
  thread th2(thread_obj(), 3);

  // define Lambda expression
  auto f = [](int x) {
    for (int i = 0; i < x; ++i) {
      cout << "thread is using lambda expression as parameter\n";
    }
  };

  // lambda expression
  thread th3(f, 3);

  // wait for threads completing

  // t1
  th1.join();

  // t2
  th2.join();

  // t3
  th3.join();

  return 0;
}



