#include "../ray.h"
#include "../segment.h"

namespace geometry {
  Ray::Ray(const Point& point, const Vector& vector) : point(point), vector(vector) {}
  Ray::Ray(const Point& first, const Point& second) : point(first), vector({first, second}) {}
  Ray& Ray::Move(const Vector& other) {
    point.Move(other);
    return *this;
  }
  bool Ray::ContainsPoint(const Point& other) const {
    Vector v2(point, other);
    return (vector.x * v2.y - vector.y * v2.x == 0) && (vector.x * v2.x + vector.y * v2.y >= 0);
  }
  bool Ray::CrossesSegment(const Segment& segment) const {
    Line line{point, {point.x + vector.x, point.y + vector.y}};
    if (ContainsPoint(segment.a) || ContainsPoint(segment.b)) {
      return true;
    }
    Vector v1(point, segment.a);
    Vector v2(point, segment.b);
    return line.CrossesSegment(segment) && (v1.x * v2.y - v1.y * v2.x) > 0;
  }
  Ray* Ray::Clone() const {
    auto new_ray = new Ray(point, vector);
    return new_ray;
  }
  std::string Ray::ToString() const {
    return "Ray(" + point.ToString() + ", " + vector.ToString() + ")";
  }
}