#include <iostream>
#include <string>
#include <vector>

#include "iterable.h"

struct test;

struct test {
  std::vector<int> vec;

  struct it_state {
    int pos;
    inline void next(test* ref) { ++pos; }
    inline void begin(test* ref) { pos = 0; }
    inline void end(test* ref) { pos = ref->vec.size(); }
    inline int& get(test* ref) { return ref->vec[pos]; }
  };
  SETUP_ITERATOR(test, int, it_state);
};

int main() {
  test a;
  a.vec.push_back(3);
  a.vec.push_back(4);
  a.vec.push_back(5);

  for (int b : a) {
    std::cout << b << std::endl;
  }

  return 0;
}
