#include <iostream>

#include <vector>
#include "iterator_tpl.h"

struct MyContainer {
  std::vector<std::string> vec;

  struct it_state {
    int pos;
    inline void next(const MyContainer* ref) { ++pos; }
    inline void begin(const MyContainer* ref) { pos = 0; }
    inline void end(const MyContainer* ref) { pos = ref->vec.size(); }
    inline std::string& get(MyContainer* ref) { return ref->vec[pos]; }
    inline const std::string& get(const MyContainer* ref) { return ref->vec[pos]; }
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

  return 0;
}
