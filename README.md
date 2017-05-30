# Simple Iterator Template

Provides a header-only C++ iterator template that is easy to adapt for any custom container

## Usage:

```C++
#include <iostream>
#include <vector>

#include "iterable.h"

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
```

Then it is easy to use the container as a normal iterator, e.g.:

```C++
int main() {
  test a;
  a.vec.push_back(3);
  a.vec.push_back(4);
  a.vec.push_back(5);

  std::cout << "mutable iterator:" << std::endl;
  for (int b : a1) {
    std::cout << b << " "; // 3 4 5
  }
  std::cout << std::endl;

  std::cout << "const iterator:" << std::endl;
  const test& a2 = a1;
  for (int b : a2) {
    std::cout << b << " "; // 3 4 5
  }
  std::cout << std::endl;

  return 0;
}
```
