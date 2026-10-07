#ifndef RAY_H
#define RAY_H

#include "ishape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
  class Ray: public IShape {
   public:
    Point point;
    Vector vector;
    Ray(const Point&, const Vector&);
    Ray(const Point&, const Point&);
    Ray& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Ray* Clone() const override;
    std::string ToString() const override;
    ~Ray() override = default;
  };
}

#endif /* RAY_H */
