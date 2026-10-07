#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
  double x = 0;
  double y = 0;
};

bool Check(Point p, Point l1, Point l2) {
  int f3 = 0;
  if (l1.x == l2.x) {
    if (p.x == l1.x) {
      if ((l1.y >= l2.y && l1.y >= p.y) || (l1.y < l2.y && l1.y <= p.y)) {
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
      if ((l1.x >= l2.x && l1.x >= p.x) || (l1.x < l2.x && l1.x <= p.x)) {
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
      if ((l1.x <= l2.x && l1.x <= p.x) || (l1.x > l2.x && l1.x >= p.x)) {
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
  return (f3 == 1);
}

int main() {
  std::cout << std::setprecision(15);
  Point l1;
  Point l2;
  Point r1;
  Point r2;
  std::cin >> l1.x >> l1.y;
  std::cin >> l2.x >> l2.y;
  std::cin >> r1.x >> r1.y;
  std::cin >> r2.x >> r2.y;
  if (Check(l1, r1, r2) || Check(l2, r1, r2) || Check(r1, l1, l2) || Check(r2, l1, l2)) {
    std::cout << "YES";
  } else {
    double ai = (l2.x - l1.x) * (r1.y - l1.y) - (l2.y - l1.y) * (r1.x - l1.x);
    double bi = (l2.x - l1.x) * (r2.y - l1.y) - (l2.y - l1.y) * (r2.x - l1.x);
    bool a = ai >= 0;
    bool b = bi >= 0;
    bool c = (a != b || (ai == 0 && bi == 0));
    ai = (r2.x - r1.x) * (l1.y - r1.y) - (r2.y - r1.y) * (l1.x - r1.x);
    bi = (r2.x - r1.x) * (l2.y - r1.y) - (r2.y - r1.y) * (l2.x - r1.x);
    a = ai >= 0;
    b = bi >= 0;
    c *= (a != b || (ai == 0 && bi == 0));
    if ((l2.y - l1.y) / (l2.x - l1.x) == (r2.y - r1.y) / (r2.x - r1.x)) {
      if (!Check(l1, r1, r2) || !Check(l2, r1, r2) || !Check(r1, l1, l2) || !Check(r2, l1, l2)) {
        c = false;
      }
    }
    c ? std::cout << "YES" : std::cout << "NO";
  }
}