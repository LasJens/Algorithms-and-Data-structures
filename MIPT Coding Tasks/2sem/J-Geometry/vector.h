#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <cmath>

namespace geometry {
  class Point;
  class Vector {
   public:
    int x;
    int y;
    Vector();
    Vector(const int& x, const int& y);
    Vector(const Point& a, const Point& b);
    ~Vector() = default;
    Vector operator+();
    Vector operator-();
    Vector operator*(int);
    Vector operator/(int);
    Vector& operator+=(Vector&);
    Vector& operator-=(Vector&);
    Vector& operator*=(int);
    Vector& operator/=(int);
    std::string ToString() const;
  };
  Vector operator+(Vector, Vector);
  Vector operator-(Vector, Vector);
  bool operator==(Vector& a, Vector& b);
}

#endif //EMPTY_VECTOR_H