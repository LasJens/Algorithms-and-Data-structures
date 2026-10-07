#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

int64_t Vect(Point l1, Point l2, Point r1, Point r2) {
  return (l2.x - l1.x) * (r2.y - r1.y) - (l2.y - l1.y) * (r2.x - r1.x);
}

int64_t Len(Point l1, Point l2) {
  return (l2.x - l1.x) * (l2.x - l1.x) + (l2.y - l1.y) * (l2.y - l1.y);
}

bool OnRay(Point l1, Point l2, Point p) {
  int64_t s = (l2.x - l1.x) * (p.x - l1.x) + (l2.y - l1.y) * (p.y - l1.y);
  int64_t v = (l2.x - l1.x) * (p.y - l1.y) - (l2.y - l1.y) * (p.x - l1.x);
  return s >= 0 && v == 0;
}

int64_t Orientation(Point p, Point q, Point r) {
  int64_t val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val == 0) {
    return 0;
  }
  return (val < 0) ? 1 : 2;
}

int64_t Square(std::vector<Point> vert, int n1) {
  int64_t sq = 0;
  Point p0;
  p0.x = 0;
  p0.y = 0;
  for (int i = 0; i < n1 - 1; ++i) {
    sq += Vect(p0, vert[i], p0, vert[i + 1]);
  }
  sq += Vect(p0, vert[n1 - 1], p0, vert[0]);
  return sq;
}

int main() {
  std::cout << std::setprecision(1);
  std::cout << std::fixed;
  int64_t n = 0;
  std::cin >> n;
  auto points = new Point[n];
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }
  std::vector<Point> hull;
  int64_t l = 0;
  for (int64_t i = 1; i < n; i++) {
    if (points[i].x < points[l].x || ((points[i].x == points[l].x) && (points[i].y < points[l].y))) {
      l = i;
    }
  }
  int64_t p = l;
  int64_t q = 0;
  do {
    hull.push_back(points[p]);
    q = (p + 1) % n;
    for (int64_t i = 0; i < n; i++) {
      int64_t o = Orientation(points[p], points[i], points[q]);
      if (o == 2) {
        q = i;
      } else if (o == 0) {
        if (!OnRay(points[q], points[p], points[i])) {
          if (Len(points[p], points[q]) < Len(points[p], points[i])) {
            q = i;
          }
        }
      }
    }
    p = q;
  } while (p != l);
  size_t left_i = 0;
  for (size_t i = 0; i < hull.size(); i++) {
    if (hull[i].x < hull[left_i].x || ((hull[i].x == hull[left_i].x) && (hull[i].y < hull[left_i].y))) {
      left_i = i;
    }
  }
  std::cout << hull.size() << '\n';
  for (size_t i = left_i; i < left_i + hull.size(); i++) {
    std::cout << hull[i % hull.size()].x << ' ' << hull[i % hull.size()].y << '\n';
  }
  std::cout << static_cast<long double>(std::abs(Square(hull, static_cast<int>(hull.size())))) / 2;
  delete[] points;
}
