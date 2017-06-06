#include <iostream>
#include <vector>
#include "../iterator_tpl.h"

struct myClass {
  std::vector<float> vec;

  // Add some sane typedefs for STL compliance:
  STL_TYPEDEFS(float);

  struct it_state {
    int pos;
    inline void begin(const myClass* ref) { pos = 0; }
    inline void next(const myClass* ref) { ++pos; }
    inline void end(const myClass* ref) { pos = ref->vec.size(); }
    inline float& get(myClass* ref) { return ref->vec[pos]; }
    inline bool cmp(const it_state& s) const { return pos != s.pos; }

    // Optional to allow operator--() and reverse iterators:
    inline void prev(const myClass* ref) { --pos; }
    // Optional to allow `const_iterator`:
    inline const float& get(const myClass* ref) const { return ref->vec[pos]; }
  };
  // Declare typedef ... iterator;, begin() and end() functions:
  SETUP_ITERATORS(myClass, float&, it_state);
  // Declare typedef ... reverse_iterator;, rbegin() and rend() functions:
  SETUP_REVERSE_ITERATORS(myClass, float&, it_state);
};

int main() {
  myClass c1;
  c1.vec.push_back(1.0);
  c1.vec.push_back(2.0);
  c1.vec.push_back(3.0);

  std::cout << std::endl;
  std::cout << "mutable iterator:" << std::endl;
  for (myClass::iterator it = c1.begin(); it != c1.end(); ++it) {
    float& val = *it;
    std::cout << val << " "; // val1 val2 val3
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "const iterator:" << std::endl;
  const myClass& c2 = c1;
  for (myClass::const_iterator it = c2.begin(); it != c2.end(); ++it) {
    const float& val = *it;
    std::cout << val << " "; // val1 val2 val3
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "reverse iterator:" << std::endl;
  for (myClass::reverse_iterator it = c1.rbegin(); it != c1.rend(); ++it) {
    std::cout << *it << " "; // val3 val2 val1
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "reverse const iterator:" << std::endl;
  for (myClass::const_reverse_iterator it = c2.rbegin(); it != c2.rend(); ++it) {
    std::cout << *it << " "; // val3 val2 val1
  }
  std::cout << std::endl;
  std::cout << std::endl;

  return 0;
}
