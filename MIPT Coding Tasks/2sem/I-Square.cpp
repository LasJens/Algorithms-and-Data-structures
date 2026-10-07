#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

int64_t Vect(Point l1, Point l2, Point r1, Point r2) {
  return (l2.x - l1.x) * (r2.y - r1.y) - (l2.y - l1.y) * (r2.x - r1.x);
}

int main() {
  int n = 0;
  std::cin >> n;
  Point p;
  p.x = 0;
  p.y = 0;
  auto vert = new Point[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> vert[i].x >> vert[i].y;
  }
  int64_t sum = 0;
  for (int i = 0; i < n - 1; ++i) {
    sum += Vect(p, vert[i], p, vert[i + 1]);
  }
  sum += Vect(p, vert[n - 1], p, vert[0]);
  if (sum < 0) {
    sum *= -1;
  }
  std::cout << std::fixed << std::setprecision(1) << static_cast<long double>(sum) / 2;
  delete[] vert;
}