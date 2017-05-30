#include <iostream>
#include <vector>

#include "iterator_tpl.h"

struct test {
  std::vector<int> vec;

  struct it_state {
    int pos;
    inline void next(const test* ref) { ++pos; }
    inline void begin(const test* ref) { pos = 0; }
    inline void end(const test* ref) { pos = ref->vec.size(); }
    inline int& get(test* ref) { return ref->vec[pos]; }
    inline const int& get(const test* ref) { return ref->vec[pos]; }
  };
  SETUP_ITERATORS(test, int, it_state);
};

int main() {
  test a1;
  a1.vec.push_back(3);
  a1.vec.push_back(4);
  a1.vec.push_back(5);

  std::cout << "mutable iterator:" << std::endl;
  for (int b : a1) {
    std::cout << b << std::endl;
  }

  std::cout << "const iterator:" << std::endl;
  const test& a2 = a1;
  for (int b : a2) {
    std::cout << b << std::endl;
  }

  return 0;
}
