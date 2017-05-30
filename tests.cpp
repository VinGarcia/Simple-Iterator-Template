#include <iostream>
#include <string>
#include <vector>

#include "iterable.h"

using namespace std;

struct test {
  std::vector<int> vec;

  SETUP_ITERATOR(test, int, int);
};

// Specialize the required functions:
template<> // Change state to next:
inline void test::iterator::next() { ++state; }
template<> // Set state to begin()
inline void test::iterator::begin() { state = 0; }
template<> // Set state to end()
inline void test::iterator::end() { state = ref->vec.size(); }
template<> // Return current value:
inline int& test::iterator::get() { return ref->vec[state]; }

int main() {
  test a;
  a.vec.push_back(3);
  a.vec.push_back(4);
  a.vec.push_back(5);
  // const test& a1 = a;

  for (int b : a) {
    std::cout << b << std::endl;
  }

  return 0;
}
