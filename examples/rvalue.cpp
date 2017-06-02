#include <iostream>
#include <vector>

#include "../iterator_tpl.h"

struct Point {
  int x;
  int y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}
  Point operator+(Point other) const {
    other.x += x;
    other.y += y;
    return other;
  }
};

struct Shape {
  std::vector<Point> vec;
};

struct Piece {
  Shape& shape;
  Point offset;
  Piece(Shape& shape, int x, int y) : shape(shape), offset(x,y) {}

  struct it_state {
    int pos;
    inline void next(const Piece* ref) { ++pos; }
    inline void begin(const Piece* ref) { pos = 0; }
    inline void end(const Piece* ref) { pos = ref->shape.vec.size(); }
    inline Point get(Piece* ref) { return ref->offset + ref->shape.vec[pos]; }
    inline bool cmp(const it_state& s) const { return pos != s.pos; }
  };
  SETUP_ITERATORS(Piece, Point, it_state);
};

int main() {
  Shape shape;
  shape.vec.emplace_back(1,2);
  shape.vec.emplace_back(2,3);
  shape.vec.emplace_back(3,4);

  Piece piece(shape, 1, 1);

  for (Point p : piece) {
    std::cout << p.x << " " << p.y << std::endl;
    // Output:
    // 2 3
    // 3 4
    // 4 5
  }

  return 0;
}
