# Simple Iterator Template

Provides a header-only C++ iterator template that is easy to adapt for any custom container

## Usage:

```C++
#include <vector>

#include "iterable.h"

using namespace std;

struct test {
  std::vector<int> vec;

  // Add the required typedefs to your container:
  MAKE_ITERABLE(int);
  // Add the non-const version of your iterator for class `test`:
  typedef iterator_tpl<test, // Container's type
                       int,  // Content's type
                       int   // type of `state` variable, used to specialize the template below.
                       > iterator;

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
```

Then it is easy to use the container as a normal iterator, e.g.:

```C++
int main() {
  test a;
  a.vec.push_back(3);
  a.vec.push_back(4);
  a.vec.push_back(5);

  for (int b : a) {
    std::cout << b << " "; // 3 4 5
  }

  return 0;
}
```
