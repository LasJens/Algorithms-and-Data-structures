#ifndef CIRCLE_H
#define CIRCLE_H

#include "ishape.h"
#include "point.h"

namespace geometry {
  class Circle: public IShape {
   public:
    Point center;
    int radius = 0;
    Circle(const Point&, const int);
    Circle& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Circle* Clone() const override;
    std::string ToString() const override;
    ~Circle() override = default;
  };
}

#endif /* CIRCLE_H */
