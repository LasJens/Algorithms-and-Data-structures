#include "../line.h"
#include "../segment.h"

namespace geometry {
  Line::Line(const Point& a, const Point& b) : a(b.y - a.y), b(a.x - b.x), c((a.y - b.y) * a.x + (b.x - a.x) * a.y) {
  }
  Line::Line(const int& a, const int& b, const int& c) : a(a), b(b), c(c) {
  }
  Line& Line::Move(const Vector& vector) {
    c += ((-a * vector.x) + (-b * vector.y));
    return *this;
  }
  bool Line::ContainsPoint(const Point& point) const {
    return (a * point.x) + (b * point.y) + c == 0;
  }
  bool Line::CrossesSegment(const Segment& segment) const {
    if (ContainsPoint(segment.a) || ContainsPoint(segment.b)) {
      return true;
    }
    if (((a * segment.a.x + b * segment.a.y + c > 0) && (a * segment.b.x + b * segment.b.y + c < 0)) ||
        ((a * segment.a.x + b * segment.a.y + c < 0) && (a * segment.b.x + b * segment.b.y + c > 0))) {
      return true;
    }
    return false;
  }
  Line* Line::Clone() const {
    auto new_line = new Line(a, b, c);
    return new_line;
  }
  std::string Line::ToString() const {
    return "Line(" + std::to_string(a) + ", " +
           std::to_string(b) + ", " + std::to_string(c) + ")";
  }
}