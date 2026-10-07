#ifndef POINT_H
#define POINT_H

#include "ishape.h"

namespace geometry {
  class Point: public IShape {
   public:
    int x = 0;
    int y = 0;
    Point();
    Point(const int&, const int&);
    Vector operator-(const Point& point) const;
    Point& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Point* Clone() const override;
    std::string ToString() const override;
    ~Point() override = default;
  };
}


#endif /* POINT_H */