#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <stack>

struct Point {
  int64_t x;
  int64_t y;
};

int64_t Vect(Point l1, Point l2, Point r1, Point r2) {
  return (l2.x - l1.x) * (r2.y - r1.y) - (l2.y - l1.y) * (r2.x - r1.x);
}

int64_t Len(Point l1, Point l2) {
  return (l2.x - l1.x) * (l2.x - l1.x) + (l2.y - l1.y) * (l2.y - l1.y);
}

std::stack<Point> Stack(Point* vert, int n) {
  for (int i = 0; i < n; ++i) {
    if ((vert[i].y < vert[0].y) || ((vert[i].y == vert[0].y) && vert[i].x < vert[0].x)) {
      std::swap(vert[i], vert[0]);
    }
  }
  Point p0 = vert[0];
  std::sort(vert + 1, vert + n, [p0](Point p1, Point p2) {
    if (Vect(p0, p1, p0, p2) == 0) {
      return Len(p0, p1) < Len(p0, p1);
    }
    return Vect(p0, p1, p0, p2) > 0;
  });
  std::stack<Point> convex_hull;
  convex_hull.push(vert[0]);
  convex_hull.push(vert[1]);
  for (int i = 2; i < n; ++i) {
    Point top = convex_hull.top();
    convex_hull.pop();
    Point pre_top = convex_hull.top();
    convex_hull.push(top);
    while (Vect(pre_top, top, top, vert[i]) < 0) {
      convex_hull.pop();
      convex_hull.pop();
      top = pre_top;
      pre_top = convex_hull.top();
      convex_hull.push(top);
    }
    if (Vect(pre_top, top, top, vert[i]) == 0) {
      convex_hull.pop();
    }
    convex_hull.push(vert[i]);
  }
  return convex_hull;
}

int64_t Square(Point* vert, int n1) {
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
  int n = 0;
  std::cin >> n;
  auto vert = new Point[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> vert[i].x >> vert[i].y;
  }
  std::stack<Point> convex_hull = Stack(vert, n);
  size_t n1 = convex_hull.size();
  auto array = new Point[n1];
  std::cout << n1 << '\n';
  for (size_t i = 0; i < n1; ++i) {
    array[i] = convex_hull.top();
    convex_hull.pop();
  }
  size_t i_left = 0;
  for (size_t i = 1; i < n1; ++i) {
    if (array[i].x < array[i_left].x) {
      i_left = i;
    }
    if ((array[i].x == array[i_left].x) && (array[i].y < array[i_left].y)) {
      i_left = i;
    }
  }
  for (size_t i = i_left; i < n1 + i_left; ++i) {
    std::cout << array[i % n1].x << " " << array[i % n1].y << '\n';
  }
  std::cout << static_cast<long double>(std::abs(Square(array, static_cast<int>(n1)))) / 2;
  delete[] vert;
  delete[] array;
}