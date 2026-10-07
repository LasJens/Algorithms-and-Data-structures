#include "../segment.h"

namespace geometry{
  bool SegmentsIntersection(const Point& a, const Point& b, const Point& c, const Point& d) {
    Line l1(a, b);
    Line l2(c, d);
    if (((l1.a * c.x + l1.b * c.y + l1.c > 0) && (l1.a * d.x + l1.b * d.y + l1.c > 0)) ||
        ((l1.a * c.x + l1.b * c.y + l1.c < 0) && (l1.a * d.x + l1.b * d.y + l1.c < 0))) {
      return false;
    }
    if (((l2.a * a.x + l2.b * a.y + l2.c > 0) && (l2.a * b.x + l2.b * b.y + l2.c > 0)) ||
        ((l2.a * a.x + l2.b * a.y + l2.c < 0) && (l2.a * b.x + l2.b * b.y + l2.c < 0))) {
      return false;
    }
    Vector v12(a, b);
    Vector v21(b, a);
    Vector v2(a, c);
    Vector v3(b, c);
    if ((v12.x * v2.y - v12.y * v2.x == 0) && (v12.x * v2.x + v12.y * v2.y >= 0) &&
        (v21.x * v3.y - v21.y * v3.x == 0) && (v21.x * v3.x + v21.y * v3.y >= 0)) {
      return true;
    }
    Vector v4(a, d);
    Vector v5(b, d);
    if ((v12.x * v4.y - v12.y * v4.x == 0) && (v12.x * v4.x + v12.y * v4.y >= 0) &&
        (v21.x * v5.y - v21.y * v5.x == 0) && (v21.x * v5.x + v21.y * v5.y >= 0)) {
      return true;
    }
    Vector v13(c, d);
    Vector v31(d, c);
    Vector v6(c, a);
    Vector v7(d, a);
    if ((v13.x * v6.y - v13.y * v6.x == 0) && (v13.x * v6.x + v13.y * v6.y >= 0) &&
        (v31.x * v7.y - v31.y * v7.x == 0) && (v31.x * v7.x + v31.y * v7.y >= 0)) {
      return true;
    }
    Vector v8(c, b);
    Vector v9(d, b);
    if ((v13.x * v8.y - v13.y * v8.x == 0) && (v13.x * v8.x + v13.y * v8.y >= 0) &&
        (v31.x * v9.y - v31.y * v9.x == 0) && (v31.x * v9.x + v31.y * v9.y >= 0)) {
      return true;
    }
    Vector v14(a, b);
    Vector v41(b, a);
    Vector v10(a, c);
    Vector v11(a, d);
    Vector v15(b, c);
    Vector v16(b, d);
    return ((v14.x * v10.y - v14.y * v10.x != 0) || (v14.x * v10.x + v14.y * v10.y < 0) ||
            (v14.x * v11.y - v14.y * v11.x != 0) || (v14.x * v11.x + v14.y * v11.y < 0)) && 
           ((v41.x * v15.y - v41.y * v15.x != 0) || (v41.x * v15.x + v41.y * v15.y < 0) ||
            (v41.x * v16.y - v41.y * v16.x != 0) || (v41.x * v16.x + v41.y * v16.y < 0));
  }

  Segment::Segment(const Point& a, const Point& b) : a(a), b(b) {
  }
  Segment& Segment::Move(const Vector& vector) {
    a.Move(vector);
    b.Move(vector);
    return *this;
  }
  bool Segment::ContainsPoint(const Point& point) const {
    if (a.x == b.x && a.y == b.y) {
      return a.x == point.x && a.y == point.y;
    }
    Vector v12(a, b);
    Vector v21(b, a);
    Vector v2(a, point);
    Vector v3(b, point);
    return (v12.x * v2.y - v12.y * v2.x == 0) && (v12.x * v2.x + v12.y * v2.y >= 0) &&
           (v21.x * v3.y - v21.y * v3.x == 0) && (v21.x * v3.x + v21.y * v3.y >= 0);
  }
  bool Segment::CrossesSegment(const Segment& segment) const {
    if (a.x == b.x && a.y == b.y) {
      return segment.ContainsPoint(a);
    }
    return SegmentsIntersection(a, b, segment.a, segment.b);
  }
  Segment* Segment::Clone() const {
    return new Segment(a, b);
  }
  std::string Segment::ToString() const {
    return "Segment(" + a.ToString() + ", " + b.ToString() + ")";
  }
}