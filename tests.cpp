#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <memory>

#include "iterable.h"

using namespace std;

struct test {
  std::vector<int> vec;

  MAKE_ITERABLE(int);
  typedef iterator_tpl<test, int, int> iterator;

  iterator begin() { return iterator::begin(this); }
  iterator end() { return iterator::end(this); }
};

// Specialize the requied functions:
template<>
void test::iterator::next() {
  value = &ref->vec[++state];
}

template<>
void test::iterator::begin() {
  state = 0;
  value = &ref->vec[0];
}

template<>
void test::iterator::end() {
  state = ref->vec.size();
  value = &ref->vec[state];
}

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
