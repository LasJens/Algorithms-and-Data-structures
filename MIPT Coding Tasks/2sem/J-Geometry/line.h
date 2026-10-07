#ifndef LINE_H
#define LINE_H

#include "ishape.h"
#include "point.h"

namespace geometry {
  class Line: public IShape {
   public:
    int a;
    int b;
    int c;
    Line(const Point& a, const Point& b);
    Line(const int& a, const int& b, const int& c);
    Line& Move(const Vector&) override;
    bool ContainsPoint(const Point&) const override;
    bool CrossesSegment(const Segment&) const override;
    Line* Clone() const override;
    std::string ToString() const override;
    ~Line() override = default;
  };
}

#endif /* LINE_H */
