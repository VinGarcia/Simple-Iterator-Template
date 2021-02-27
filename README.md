# Simple Iterator Template

Provides a header-only C++ iterator template that is easy to adapt for any custom container.

## Features:

- Single header.
- STL Compliant.
- No efficiency loss, it is as efficient as it could possibly be.
- Really easy to understand.
- Concise: on simple cases it takes only 10 lines to adapt a container,
  and on more complex cases it takes only a few extra lines.
- Implements Forward Iterator, Input Iterator, Output Iterator and Bidirectional Iterator.
- Compatible with all C++ standards (see `example/reverse.cpp`).

It not only provides a forward `iterator` to your class but also a `const_iterator`
reusing the same definitions except for the `get()` function, for whom a const
version must be provided (still included in the 9 lines).

It also includes an optional `reversed_iterator` and `const_reversed_iterator`, to add them you need to add a function `prev()` described below and a single macro that accepts the same arguments used for the normal iterators.

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
  SETUP_ITERATORS(myClass, float&, it_state);
};
```

Then it is easy to use the container as a normal iterator, e.g.:

```C++
int main() {
  myClass a1;
  a1.vec.push_back(1.0);
  a1.vec.push_back(2.0);
  a1.vec.push_back(3.0);

  std::cout << "mutable iterator:" << std::endl;
  for (float& val : a1) {
    std::cout << val << " "; // 1 2 3
  }
  std::cout << std::endl;

  std::cout << "const iterator:" << std::endl;
  const myClass& a2 = a1;
  for (const float& val : a2) {
    std::cout << val << " "; // 1 2 3
  }
  std::cout << std::endl;

  return 0;
}
```

## Add reverse iterators:

To add reverse iterators only two things are required:

1. Add a void `prev(const myClass* ref) { --pos; }` function to `state_it`.
2. Add the macro `SETUP_REVERSE_ITERATORS` with the same 3 arguments as `SETUP_ITERATORS`.

```C++
struct myClass {
  std::vector<float> vec;

  struct it_state {
    int pos;
    inline void next(const myClass* ref) { ++pos; }
    inline void prev(const myClass* ref) { --pos; } // <-- Add `prev()`
    inline void begin(const myClass* ref) { pos = 0; }
    inline void end(const myClass* ref) { pos = ref->vec.size(); }
    inline float& get(myClass* ref) { return ref->vec[pos]; }
    inline const float& get(const myClass* ref) { return ref->vec[pos]; }
    inline bool cmp(const it_state& s) const { return pos != s.pos; }
  };
  SETUP_ITERATORS(myClass, float&, it_state);
  SETUP_REVERSE_ITERATORS(myClass, float&, it_state); // <-- Add REVERSE_ITERATORS macro
};
```

Then it is possible to use `rbegin()` and `rend()` normally:

```C++
int main() {
  myClass a1;
  const myClass& a2 = a1;

  a1.vec.push_back(1.0);
  a1.vec.push_back(2.0);
  a1.vec.push_back(3.0);

  std::cout << "mutable reverse iterator:" << std::endl;
  for (auto it = a1.rbegin(); it != a1.rend(); ++it) {
    float& val = *it;
    std::cout << val << " "; // 3 2 1
  }
  std::cout << std::endl;

  std::cout << "const reverse iterator:" << std::endl;
  for (auto it = a2.rbegin(); it != a2.rend(); ++it) {
    const float& val = *it;
    std::cout << val << " "; // 3 2 1
  }
  std::cout << std::endl;

  return 0;
}
```

## Returning RValues

Returning by reference is nice, it allows you to change the internal values of the iterator
and prevents unnecessary copies. However, sometimes it is not possible.

For these cases the library allows you to specify the template with a type `float` instead
of `float&`, e.g.:

```C++
  SETUP_ITERATORS(myClass, float, it_state);
  SETUP_REVERSE_ITERATORS(myClass, float, it_state);
```

This allows for the get() functions to return `float` when returning `float&`
would not be possible, e.g.:

```C++
  struct it_state {
    int pos;
    inline void next(const myClass* ref) { ++pos; }
    inline void prev(const myClass* ref) { --pos; }
    inline void begin(const myClass* ref) { pos = 0; }
    inline void end(const myClass* ref) { pos = ref->vec.size(); }
    inline float get(myClass* ref) { return 1 + ref->vec[pos]; }
    inline const float get(const myClass* ref) { return 1 + ref->vec[pos]; }
    inline bool cmp(const it_state& s) const { return pos != s.pos; }
  };
```

## STL Typedefs

To offer full compliance with STL iterators there is an easy way to add some sane defaults for the required typedefs to your class, the macro `STL_TYPEDEFS`:

```C++
struct myClass {
  std::vector<float> vec;

  STL_TYPEDEFS(float); // (Optional)
  struct it_state {
    int pos;
    inline void next(const myClass* ref) { ++pos; }
    inline void prev(const myClass* ref) { --pos; } // (Optional)
    inline void begin(const myClass* ref) { pos = 0; }
    inline void end(const myClass* ref) { pos = ref->vec.size(); }
    inline float& get(myClass* ref) { return ref->vec[pos]; }
    inline const float& get(const myClass* ref) { return ref->vec[pos]; }
    inline bool cmp(const it_state& s) const { return pos != s.pos; }
  };
  SETUP_ITERATORS(myClass, float&, it_state);
  SETUP_REVERSE_ITERATORS(myClass, float&, it_state); // (Optional)
};
```

This adds the following typedefs to your class (you might just write them by hand if you prefer):

```C++
  typedef std::ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
```

## I don't like macros, can I skip them?

Yes, actually even without the macros the template library is still quite concise in comparison to writing everything manually:

```C++
struct myClass {
  std::vector<float> vec;

  typedef std::ptrdiff_t difference_type;
  typedef size_t size_type;
  typedef float value_type;
  typedef float* pointer;
  typedef const float* const_pointer;
  typedef float& reference;
  typedef const float& const_reference;

  struct it_state {
    int pos;
    inline void next(const myClass* ref) { ++pos; }
    inline void prev(const myClass* ref) { --pos; }
    inline void begin(const myClass* ref) { pos = 0; }
    inline void end(const myClass* ref) { pos = ref->vec.size(); }
    inline float& get(myClass* ref) { return ref->vec[pos]; }
    inline const float& get(const myClass* ref) { return ref->vec[pos]; }
    inline bool cmp(const it_state& s) const { return pos != s.pos; }
  };

  // Mutable Iterator:
  typedef iterator_tpl::iterator<myClass, float&, it_state> iterator;
  iterator begin() { return iterator::begin(this); }
  iterator end() { return iterator::end(this); }

  // Const Iterator:
  typedef iterator_tpl::const_iterator<myClass, float&, it_state> const_iterator;
  const_iterator begin() const { return const_iterator::begin(this); }
  const_iterator end() const { return const_iterator::end(this); }

  // Reverse `it_state`:
  struct reverse_it_state : public it_state {
    inline void next(const myClass* ref) { it_state::prev(ref); }
    inline void prev(const myClass* ref) { it_state::next(ref); }
    inline void begin(const myClass* ref) { it_state::end(ref); it_state::prev(ref);}
    inline void end(const myClass* ref) { it_state::begin(ref); it_state::prev(ref);}
  };

  // Mutable Reverse Iterator:
  typedef iterator_tpl::iterator<myClass, float&, reverse_it_state> reverse_iterator;
  reverse_iterator rbegin() { return reverse_iterator::begin(this); }
  reverse_iterator rend() { return reverse_iterator::end(this); }

  // Const Reverse Iterator:
  typedef iterator_tpl::const_iterator<myClass, float&, reverse_it_state> const_reverse_iterator;
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator::begin(this);
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator::end(this);
  }
};
```

You can then run the `iterators`, `const_iterators`, and `reversed_iterators` as before:

```C++
int main() {
  myClass a1;
  const myClass& a2 = a1;

  a1.vec.push_back(1.0);
  a1.vec.push_back(2.0);
  a1.vec.push_back(3.0);

  std::cout << "mutable iterator:" << std::endl;
  for (float& val : a1) {
    std::cout << val << " "; // 1 2 3
  }
  std::cout << std::endl;

  std::cout << "const iterator:" << std::endl;
  for (const float& val : a2) {
    std::cout << val << " "; // 1 2 3
  }
  std::cout << std::endl;

  std::cout << "mutable reverse iterator:" << std::endl;
  for (auto it = a1.rbegin(); it != a1.rend(); ++it) {
    float& val = *it;
    std::cout << val << " "; // 3 2 1
  }
  std::cout << std::endl;

  std::cout << "const reverse iterator:" << std::endl;
  for (auto it = a2.rbegin(); it != a2.rend(); ++it) {
    const float& val = *it;
    std::cout << val << " "; // 3 2 1
  }
  std::cout << std::endl;

  return 0;
}
```

## Macro Colisions:

For having a way to avoid macro colisions a new version of the macros was
created, so for every macro you see on the examples you can also use the
fullnamed version below if macro colisions is a concern:

- `VGSI_SETUP_ITERATORS(C, T, S)`
- `VGSI_SETUP_MUTABLE_ITERATOR(C, T, S)`
- `VGSI_SETUP_CONST_ITERATOR(C, T, S)`
- `VGSI_SETUP_REVERSE_ITERATORS(C, T, S)`
- `VGSI_SETUP_MUTABLE_RITERATOR(C, T, S)`
- `VGSI_SETUP_CONST_RITERATOR(C, T, S)`
- `VGSI_STL_TYPEDEFS(T)`
