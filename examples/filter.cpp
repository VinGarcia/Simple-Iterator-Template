
#include <iostream>
#include <vector>

#include "../iterator_tpl.h"

struct Point {
  int x;
  int y;
  Point(int x, int y) : x(x), y(y) {}
};

struct Shape {
  std::vector<Point> vec;

  static bool some_filter (const Point& p) {
    return p.x > p.y;
  }

  struct it_state {
    int pos;
    int end_pos;

    // Find next valid item:
    inline void next(const Shape* ref) {
      ++pos;
      while (some_filter(ref->vec[pos]) && pos < end_pos) ++pos;
    }

    // Prepare the iterator:
    inline void begin(const Shape* ref) {
      pos = -1;
      end_pos = ref->vec.size();
      // Find first valid item:
      next(ref);
    }

    inline void end(const Shape* ref) { pos = ref->vec.size(); }
    inline Point& get(Shape* ref) { return ref->vec[pos]; }
    inline bool equals(const it_state& s) const { return pos == s.pos; }

    // Optional for const_iterator to work:
    inline const Point& get(const Shape* ref) { return ref->vec[pos]; }
  };
  SETUP_ITERATORS(Shape, Point&, it_state);
};

int main() {
  Shape shape;
  shape.vec.emplace_back(1,2);
  shape.vec.emplace_back(2,3);
  shape.vec.emplace_back(3,4);
  shape.vec.emplace_back(2,1);
  shape.vec.emplace_back(3,2);
  shape.vec.emplace_back(4,3);

  for (Point p : shape) {
    std::cout << p.x << " " << p.y << std::endl;
    // Output:
    // 1 2
    // 2 3
    // 3 4
  }

  return 0;
}
