#include "../circle.h"
#include "../segment.h"

namespace geometry {
  Circle::Circle(const Point& point, const int radius) : center(point), radius(radius) {}
  Circle& Circle::Move(const Vector& vector) {
    center.Move(vector);
    return *this;
  }
  bool Circle::ContainsPoint(const Point& point) const {
    return (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y) <= radius * radius;
  }
  bool Circle::CrossesSegment(const geometry::Segment& segment) const {
    if (segment.a.x == segment.b.x && segment.a.y == segment.b.y) {
      return (segment.a.x - center.x) * (segment.a.x - center.x) +
             (segment.a.y - center.y) * (segment.a.y - center.y) == radius * radius;
    }
    if ((segment.a.x - center.x) * (segment.a.x - center.x) +
        (segment.a.y - center.y) * (segment.a.y - center.y) == radius * radius) {
      return true;
    }
    if ((segment.b.x - center.x) * (segment.b.x - center.x) +
        (segment.b.y - center.y) * (segment.b.y - center.y) == radius * radius) {
      return true;
    }
    if (ContainsPoint(segment.a) != ContainsPoint(segment.b)) {
      return true;
    }
    if (ContainsPoint(segment.a) && ContainsPoint(segment.b)) {
      return false;
    }
    Vector v1{segment.a, segment.b};
    Vector v2{segment.a, center};
    Vector v3{segment.b, center};
    if (v1.x * v2.x + v1.y * v2.y < 0) {
      return (segment.a.x - center.x) * (segment.a.x - center.x) + (segment.a.y - center.y) * (segment.a.y - center.y) ==
             radius * radius && (!ContainsPoint(segment.b));
    }
    if (v1.x * v3.x + v1.y * v3.y > 0) {
      return (segment.b.x - center.x) * (segment.b.x - center.x) + (segment.b.y - center.y) * (segment.b.y - center.y) ==
             radius * radius && (!ContainsPoint(segment.b));
    }
    Line l(segment.a, segment.b);
    return static_cast<int64_t>(l.a * center.x + l.b * center.y + l.c) * static_cast<int64_t>(l.a * center.x + l.b * center.y + l.c) <=
           static_cast<int64_t>(l.a * l.a + l.b * l.b) * static_cast<int64_t>(radius * radius);
  }
  Circle* Circle::Clone() const {
    auto new_circle = new Circle(center, radius);
    return new_circle;
  }
  std::string Circle::ToString() const {
    return "Circle(" + center.ToString() + ", " + std::to_string(radius) + ")";
  }
}