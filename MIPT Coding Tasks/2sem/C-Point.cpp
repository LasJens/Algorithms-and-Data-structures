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
  int f1 = 0;
  int f2 = 0;
  int f3 = 0;
  if (l1.x == l2.x) {
    if (p.x == l1.x) {
      f1 = 1;
      if ((l1.y >= l2.y && l1.y >= p.y) || (l1.y < l2.y && l1.y <= p.y)) {
        f2 = 1;
        if (l1.y >= l2.y) {
          if (p.y <= l1.y && p.y >= l2.y) {
            f3 = 1;
          }
        } else if (l1.y < l2.y) {
          if (p.y >= l1.y && p.y <= l2.y) {
            f3 = 1;
          }
        }
      }
    }
  } else if (l1.y == l2.y) {
    if (p.y == l1.y) {
      f1 = 1;
      if ((l1.x >= l2.x && l1.x >= p.x) || (l1.x < l2.x && l1.x <= p.x)) {
        f2 = 1;
        if (l1.x >= l2.x) {
          if (p.x <= l1.x && p.x >= l2.x) {
            f3 = 1;
          }
        } else {
          if (p.x >= l1.x && p.x <= l2.x) {
            f3 = 1;
          }
        }
      }
    }
  } else {
    double k = (l2.y - l1.y) / (l2.x - l1.x);
    double b = l1.y - k * l1.x;
    if (p.y == k * p.x + b) {
      f1 = 1;
      if ((l1.x <= l2.x && l1.x <= p.x) || (l1.x > l2.x && l1.x >= p.x)) {
        f2 = 1;
        if (l1.x <= l2.x) {
          if (p.x >= l1.x && p.x <= l2.x) {
            f3 = 1;
          }
        } else {
          if (p.x <= l1.x && p.x >= l2.x) {
            f3 = 1;
          }
        }
      }
    }
  }
  if (f1 == 1) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
  if (f2 == 1) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
  if (f3 == 1) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
}