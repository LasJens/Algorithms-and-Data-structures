#include "../polygon.h"
#include <cmath>

namespace geometry {
  Polygon::Polygon(const std::vector<Point> points) : vertexes(points) {
  }
  Polygon& Polygon::Move(const Vector& vector) {
    for (size_t i = 0; i < vertexes.size(); ++i) {
      vertexes[i].Move(vector);
    }
    return *this;
  }
  bool Polygon::ContainsPoint(const Point& point) const {
    return IsInside(point, vertexes, vertexes.size());
  }
  bool Polygon::CrossesSegment(const Segment& segment) const {
    for (size_t i = 0; i < vertexes.size(); ++i) {
      if (segment.CrossesSegment({vertexes[i], vertexes[(i + 1) % vertexes.size()]})) {
        return true;
      }
    }
    return false;
  }
  Polygon* Polygon::Clone() const {
    return new Polygon(vertexes);
  }
  std::string Polygon::ToString() const {
    std::string string = "Polygon(";
    for (size_t i = 0; i < vertexes.size() - 1; ++i) {
      string += (vertexes[i].ToString() + ", ");
    }
    string += (vertexes[vertexes.size() - 1].ToString() + ")");
    return string;
  }
  bool Check2(Point p, Point l1, Point l2) {
    int f3 = 0;
    if (((p.x - l1.x) * (l2.y - p.y) - (p.y - l1.y) * (l2.x - p.x) == 0) &&
        ((p.x - l1.x) * (l2.x - p.x) + (p.y - l1.y) * (l2.y - p.y) >= 0)) {
      f3 = 1;
    }
    return (f3 == 1);
  }
  bool Cross2(Point l1, Point l2, Point r1, Point r2) {
    bool c = true;
    if (Check2(l1, r1, r2) || Check2(l2, r1, r2) || Check2(r1, l1, l2) || Check2(r2, l1, l2)) {
    } else {
      int64_t ai = (l2.x - l1.x) * (r1.y - l1.y) - (l2.y - l1.y) * (r1.x - l1.x);
      int64_t bi = (l2.x - l1.x) * (r2.y - l1.y) - (l2.y - l1.y) * (r2.x - l1.x);
      bool a = ai >= 0;
      bool b = bi >= 0;
      c = (a != b || (ai == 0 && bi == 0));
      ai = (r2.x - r1.x) * (l1.y - r1.y) - (r2.y - r1.y) * (l1.x - r1.x);
      bi = (r2.x - r1.x) * (l2.y - r1.y) - (r2.y - r1.y) * (l2.x - r1.x);
      a = ai >= 0;
      b = bi >= 0;
      c *= (a != b || (ai == 0 && bi == 0));
      if ((l2.y - l1.y) * (r2.x - r1.x) == (l2.x - l1.x) * (r2.y - r1.y)) {
        c = false;
      }
    }
    return c;
  }
  bool IsInside(const Point& p, const std::vector<Point>& vert, size_t n) {
    int mx = 0;
    for (size_t i = 0; i < n; ++i) {
      if (mx < vert[i].x) {
        mx = vert[i].x;
      }
    }
    Point hor;
    hor.x = mx + 1;
    hor.y = p.y;
    int counter = 0;
    for (size_t i = 0; i < n - 1; ++i) {
      if (Check2(p, vert[i], vert[i + 1])) {
        counter = 1;
      }
    }
    if (Check2(p, vert[n - 1], vert[0])) {
      counter = 1;
    }
    for (size_t i = 0; i < n; ++i) {
      if (p.x == vert[i].x && p.y == vert[i].y) {
        counter = 1;
      }
    }
    if (counter == 1) {
      return true;
    }
    for (size_t i = 0; i < n - 1; ++i) {
      if (Cross2(vert[i], vert[i + 1], p, hor) ||
          ((vert[i].x == vert[i + 1].x) && (p.x <= vert[i].x) && (p.y <= std::max(vert[i].y, vert[i + 1].y)) &&
           (p.y >= std::min(vert[i].y, vert[i + 1].y)))) {
        if (vert[i].y == vert[i + 1].y) {
        } else if (p.y == std::max(vert[i].y, vert[i + 1].y)) {
          ++counter;
        } else if (p.y != vert[i].y && p.y != vert[i + 1].y) {
          ++counter;
        }
      }
    }
    if (Cross2(vert[n - 1], vert[0], p, hor) ||
        ((vert[n - 1].x == vert[0].x) && (p.x <= vert[n - 1].x) && (p.y <= std::max(vert[n - 1].y, vert[0].y)) &&
         (p.y >= std::min(vert[n - 1].y, vert[0].y)))) {
      if (vert[n - 1].y == vert[0].y) {
      } else if (p.y == std::max(vert[n - 1].y, vert[0].y)) {
        ++counter;
      } else if (p.y != vert[n - 1].y && p.y != vert[0].y) {
        ++counter;
      }
    }
    if (counter % 2 == 0) {
      return false;
    }
    return true;
  }
}