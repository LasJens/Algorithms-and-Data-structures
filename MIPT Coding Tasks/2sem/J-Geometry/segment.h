#ifndef SEGMENT_H
#define SEGMENT_H

#include "ishape.h"
#include "point.h"
#include "line.h"

namespace geometry {
  class Segment: public IShape{
   public:
    Point a;
    Point b;
    Segment(const Point&, const Point&);
    Segment& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Segment* Clone() const override;
    std::string ToString() const override;
    ~Segment() override = default;
  };
  bool SegmentsIntersection(const Point&, const Point&, const Point&, const Point&);
  bool Check(const Point&, const Point&, const Point&);

}

#endif /* SEGMENT_H */