#include <iostream>

#include <vector>
#include "iterator_tpl.h"

#define ASSERT(COND) if ((COND) == 0) {\
  std::cout << std::string("Assertion error for cond: " #COND)\
  << std::endl;\
  throw "failed";\
}

struct MyContainer {
  std::vector<std::string> vec;

  // Add some sane typedefs to make it STL friendly:
  STL_TYPEDEFS(std::string); // (This step is optional)

  struct it_state {
    int pos;
    inline void next(const MyContainer* ref) { ++pos; }
    inline void begin(const MyContainer* ref) { pos = 0; }
    inline void end(const MyContainer* ref) { pos = ref->vec.size(); }
    inline std::string& get(MyContainer* ref) { return ref->vec[pos]; }
    inline const std::string& get(const MyContainer* ref) const { return ref->vec[pos]; }
  };
  SETUP_ITERATORS(MyContainer, std::string, it_state);
};

int main() {
  MyContainer c1;
  c1.vec.push_back("val1");
  c1.vec.push_back("val2");
  c1.vec.push_back("val3");

  std::cout << std::endl;
  std::cout << "mutable iterator:" << std::endl;
  for (std::string& str : c1) {
    std::cout << str << std::endl; // val1 val2 val3
  }

  std::cout << std::endl;
  std::cout << "const iterator:" << std::endl;
  const MyContainer& c2 = c1;
  for (const std::string& str : c2) {
    std::cout << str << std::endl; // val1 val2 val3
  }
  std::cout << std::endl;

  // Testing copy-constructor and copy-assignment between
  // const_iterators and iterators:
  MyContainer::const_iterator it1 = c1.end();
  ASSERT(it1 == c2.end());
  MyContainer::const_iterator it2;
  it1 = c1.begin();
  ASSERT(it1 != c2.end());
  it2 = c1.begin();
  ASSERT(it2 == c2.begin());

  // Testing comparisons between const and normal iterators:
  ASSERT(it2 == c2.begin());
  ASSERT((it2 != c2.begin()) == 0);
  ASSERT(c2.begin() == it2);
  ASSERT((c2.begin() != it2) == 0);

  return 0;
}
