#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
  double x = 0;
  double y = 0;
};

int main() {
  std::cout << std::setprecision(15);
  Point l1;
  Point l2;
  Point p;
  std::cin >> p.x >> p.y;
  std::cin >> l1.x >> l1.y;
  std::cin >> l2.x >> l2.y;
  double b = l2.x - l1.x;
  double a = l1.y - l2.y;
  double c = -a * l1.x - b * l1.y;
  double r1 = 0;
  double r2 = 0;
  double r3 = 0;
  double r31 = 0;
  double r32 = 0;
  r1 = std::abs((a * p.x + b * p.y + c) / std::sqrt(a * a + b * b));
  if ((l2.x - l1.x) * (p.x - l1.x) + (l2.y - l1.y) * (p.y - l1.y) >= 0) {
    r2 = r1;
  } else {
    r2 = std::sqrt((l1.x - p.x) * (l1.x - p.x) + (l1.y - p.y) * (l1.y - p.y));
  }
  if ((l2.x - l1.x) * (p.x - l1.x) + (l2.y - l1.y) * (p.y - l1.y) >= 0 &&
      (l1.x - l2.x) * (p.x - l2.x) + (l1.y - l2.y) * (p.y - l2.y) >= 0) {
    r3 = r1;
  } else {
    r31 = std::sqrt((l1.x - p.x) * (l1.x - p.x) + (l1.y - p.y) * (l1.y - p.y));
    r32 = std::sqrt((l2.x - p.x) * (l2.x - p.x) + (l2.y - p.y) * (l2.y - p.y));
    r31 < r32 ? r3 = r31 : r3 = r32;
  }
  std::cout << r1 << '\n' << r2 << '\n' << r3;
}