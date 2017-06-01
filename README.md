# Simple Iterator Template

Provides a header-only C++ iterator template that is easy to adapt for any custom container.

## Features:

- Single header.
- STL Compliant (needs some improvement).
- No efficience loss, it is as efficient as it could possible be.
- Really easy to understand.
- Concise, on simple cases it takes only 9 lines to adapt a container,
  and on more complex cases it takes only a few lines more.

It not only provides a forward `iterator` to your class but also a `const_iterator`
reusing the same definitions except for the `get()` function, for whom a const
version must be provided (still included in the 9 lines).

## Usage:

```C++
#include <iostream>
#include <vector>

#include "iterator_tpl.h"

struct myClass {
  std::vector<float> vec;

  struct it_state {
    int pos;
    inline void next(const myClass* ref) { ++pos; }
    inline void begin(const myClass* ref) { pos = 0; }
    inline void end(const myClass* ref) { pos = ref->vec.size(); }
    inline float& get(myClass* ref) { return ref->vec[pos]; }
    inline const float& get(const myClass* ref) { return ref->vec[pos]; }
    inline bool cmp(const it_state& s) const { return pos != s.pos; }
  };
  SETUP_ITERATORS(myClass, float, it_state);
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
