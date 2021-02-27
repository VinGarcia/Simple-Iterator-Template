#include <iostream>
#include <vector>
#include "iterator_tpl.h"

#define ASSERT(COND) if ((COND) == 0) {\
  std::cout << std::string("Assertion error for cond: " #COND)\
  << std::endl;\
  throw "failed";\
}

struct myClass {
  std::vector<float> vec;

  struct it_state {
    int pos;
    inline void next(const myClass* ref) { ++pos; }
    inline void prev(const myClass* ref) { --pos; }
    inline void begin(const myClass* ref) { pos = 0; }
    inline void end(const myClass* ref) { pos = ref->vec.size(); }
    inline float& get(myClass* ref) { return ref->vec[pos]; }
    inline const float& get(const myClass* ref) const { return ref->vec[pos]; }
    inline bool equals(const it_state& s) const { return pos == s.pos; }
  };
  SETUP_ITERATORS(myClass, float&, it_state);
  SETUP_REVERSE_ITERATORS(myClass, float&, it_state);
};

// This class's iterator will return only rvalues, i.e.
// `float` instead of `float&`
struct myClass_rvalue {
  std::vector<float> vec;

  struct it_state {
    int pos;
    inline void next(const myClass_rvalue* ref) { ++pos; }
    inline void prev(const myClass_rvalue* ref) { --pos; }
    inline void begin(const myClass_rvalue* ref) { pos = 0; }
    inline void end(const myClass_rvalue* ref) { pos = ref->vec.size(); }
    inline float get(myClass_rvalue* ref) { return ref->vec[pos] - 1; }
    inline const float get(const myClass_rvalue* ref) { return ref->vec[pos] - 1; }
    inline bool equals(const it_state& s) const { return pos == s.pos; }
  };
  SETUP_ITERATORS(myClass_rvalue, float, it_state);
  SETUP_REVERSE_ITERATORS(myClass_rvalue, float, it_state);
};

int main() {
  myClass c1;
  c1.vec.push_back(1.0);
  c1.vec.push_back(2.0);
  c1.vec.push_back(3.0);

  std::cout << std::endl;
  std::cout << "mutable iterator:" << std::endl;
  for (float& val : c1) {
    std::cout << val << " "; // val1 val2 val3
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "const iterator:" << std::endl;
  const myClass& c2 = c1;
  for (const float& val : c2) {
    std::cout << val << " "; // val1 val2 val3
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "reversed iterator:" << std::endl;
  for (auto it = c1.rbegin(); it != c1.rend(); ++it) {
    std::cout << *it << " "; // val3 val2 val1
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "reversed const iterator:" << std::endl;
  for (auto it = c2.rbegin(); it != c2.rend(); ++it) {
    std::cout << *it << " "; // val3 val2 val1
  }
  std::cout << std::endl;

  myClass_rvalue c1_rvalue;
  c1_rvalue.vec.push_back(1.0);
  c1_rvalue.vec.push_back(2.0);
  c1_rvalue.vec.push_back(3.0);
  const myClass_rvalue& c2_rvalue = c1_rvalue;

  std::cout << std::endl;
  std::cout << "rvalue mutable iterator:" << std::endl;
  for (auto it = c1_rvalue.begin(); it != c1_rvalue.end(); ++it) {
    float val = *it;
    std::cout << val << " "; // val3 val2 val1
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "rvalue const iterator:" << std::endl;
  for (auto it = c2_rvalue.begin(); it != c2_rvalue.end(); ++it) {
    float val = *it;
    std::cout << val << " "; // val3 val2 val1
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "rvalue reversed mutable iterator:" << std::endl;
  for (auto it = c1_rvalue.rbegin(); it != c1_rvalue.rend(); ++it) {
    float val = *it;
    std::cout << val << " "; // val3 val2 val1
  }
  std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "rvalue reversed const iterator:" << std::endl;
  for (auto it = c2_rvalue.rbegin(); it != c2_rvalue.rend(); ++it) {
    float val = *it;
    std::cout << val << " "; // val3 val2 val1
  }
  std::cout << std::endl;
  std::cout << std::endl;

  // Testing copy-constructor and copy-assignment between
  // const_iterators and iterators:
  myClass::const_iterator it1 = c1.end();
  ASSERT(it1 == c2.end());
  myClass::const_iterator it2;
  it1 = c1.begin();
  ASSERT(it1 != c2.end());
  it2 = c1.begin();
  ASSERT(it2 == c2.begin());

  // Testing comparisons between const and normal iterators:
  ASSERT(it2 == c2.begin());
  ASSERT((it2 != c2.begin()) == 0);
  ASSERT(c2.begin() == it2);
  ASSERT((c2.begin() != it2) == 0);

  // Testing operators++ pre and post-fixed:
  ASSERT(*c1.begin() == 1);
  ASSERT(*(++c1.begin()) == 2);
  ASSERT(*(c1.begin()++) == 1);

  // Testing operators++ pre and post-fixed for const classes:
  ASSERT(*c2.begin() == 1);
  ASSERT(*(++c2.begin()) == 2);
  ASSERT(*(c2.begin()++) == 1);

  return 0;
}
