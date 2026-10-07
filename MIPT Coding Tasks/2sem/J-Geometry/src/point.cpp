#include "../segment.h"
#include "../point.h"

namespace geometry {
  Point::Point() : x(0), y(0) {
  }
  Point::Point(const int& x0, const int& y0) : x(x0), y(y0) {
  }
  Vector Point::operator-(const Point& point) const {
    return {x - point.x, y - point.y};
  }
  Point& Point::Move(const Vector& vector) {
    x += vector.x;
    y += vector.y;
    return *this;
  }
  bool Point::ContainsPoint(const Point& point) const {
    return point.x == x && point.y == y;
  }
  bool Point::CrossesSegment(const Segment& segment) const {
    Vector v12(segment.a, segment.b);
    Vector v21(segment.b, segment.a);
    Vector v2(segment.a, *this);
    Vector v3(segment.b, *this);
    return (v12.x * v2.y - v12.y * v2.x == 0) && (v12.x * v2.x + v12.y * v2.y >= 0) &&
           (v21.x * v3.y - v21.y * v3.x == 0) && (v21.x * v3.x + v21.y * v3.y >= 0);
  }
  Point* Point::Clone() const {
    auto new_point_ptr = new Point;
    (*new_point_ptr).x = x;
    (*new_point_ptr).y = y;
    return new_point_ptr;
  }
  std::string Point::ToString() const {
    return "Point(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }
}