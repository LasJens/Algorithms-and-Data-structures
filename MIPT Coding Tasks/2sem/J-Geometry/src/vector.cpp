#include <iostream>
#include "../point.h"
#include "../vector.h"
#include <string>

namespace geometry {
  Vector::Vector() : x(0), y(0) {
  }
  Vector::Vector(const int& x0, const int& y0) : x(x0), y(y0) {
  }
  Vector::Vector(const Point& a, const Point& b) : x(b.x - a.x), y(b.y - a.y) {
  }
  Vector operator+(Vector a) {
    return {+a.x, +a.y};
  }
  Vector operator-(Vector a) {
    return {-a.x, -a.y};
  }
  Vector operator*(Vector a, int c) {
    return {c * a.x, c * a.y};
  }
  Vector operator/(Vector a, int c) {
    return {a.x / c, a.y / c};
  }
  Vector& operator+=(Vector& a, Vector& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
  }
  Vector& operator-=(Vector& a, Vector& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
  }
  Vector& operator*=(Vector& a, int c) {
    a.x *= c;
    a.y *= c;
    return a;
  }
  Vector& operator/=(Vector& a, int c) {
    a.x /= c;
    a.y /= c;
    return a;
  }
  Vector operator+(Vector a, Vector b) {
    return {a.x + b.x, a.y + b.y};
  }
  Vector operator-(Vector a, Vector b) {
    return {a.x - b.x, a.y - b.y};
  }
  bool operator==(Vector& a, Vector& b) {
    return (a.x == b.x) && (a.y == b.y);
  }
  std::string Vector::ToString() const {
    return "Vector(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }
}
