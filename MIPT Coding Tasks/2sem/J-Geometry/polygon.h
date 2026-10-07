#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "ishape.h"
#include "point.h"
#include "segment.h"

namespace geometry {
  class Polygon: public IShape {
   public:
    std::vector<Point> vertexes;
    explicit Polygon(const std::vector<Point>);
    Polygon& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Polygon* Clone() const override;
    std::string ToString() const override;
    ~Polygon() override = default;
  };
  bool Check(const Point&, const Point&, const Point&);
  bool Cross(const Point&, const Point&, const Point&, const Point&);
  bool IsInside(const Point&, const std::vector<Point>&, size_t);
}

#endif /* POLYGON_H */
