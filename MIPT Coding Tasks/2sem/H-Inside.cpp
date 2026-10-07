#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

bool Check(Point p, Point l1, Point l2) {
  int f3 = 0;
  if (((p.x - l1.x) * (l2.y - p.y) - (p.y - l1.y) * (l2.x - p.x) == 0) &&
      ((p.x - l1.x) * (l2.x - p.x) + (p.y - l1.y) * (l2.y - p.y) >= 0)) {
    f3 = 1;
  }
  return (f3 == 1);
}

bool Cross(Point l1, Point l2, Point r1, Point r2) {
  bool c = true;
  if (Check(l1, r1, r2) || Check(l2, r1, r2) || Check(r1, l1, l2) || Check(r2, l1, l2)) {
  } else {
    int64_t ai = (l2.x - l1.x) * (r1.y - l1.y) - (l2.y - l1.y) * (r1.x - l1.x);
    int64_t bi = (l2.x - l1.x) * (r2.y - l1.y) - (l2.y - l1.y) * (r2.x - l1.x);
    bool a = ai >= 0;
    bool b = bi >= 0;
    c = (a != b || (ai == 0 && bi == 0));
    ai = (r2.x - r1.x) * (l1.y - r1.y) - (r2.y - r1.y) * (l1.x - r1.x);
    bi = (r2.x - r1.x) * (l2.y - r1.y) - (r2.y - r1.y) * (l2.x - r1.x);
    a = ai >= 0;
    b = bi >= 0;
    c *= (a != b || (ai == 0 && bi == 0));
    if ((l2.y - l1.y) * (r2.x - r1.x) == (l2.x - l1.x) * (r2.y - r1.y)) {
      c = false;
    }
  }
  return c;
}

int main() {
  std::cout << std::setprecision(15);
  int n = 0;
  std::cin >> n;
  Point p;
  std::cin >> p.x >> p.y;
  auto vert = new Point[n];
  int64_t mx = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> vert[i].x >> vert[i].y;
    if (mx < vert[i].x) {
      mx = vert[i].x;
    }
  }
  Point hor;
  hor.x = mx + 1;
  hor.y = p.y;
  int counter = 0;
  for (int i = 0; i < n - 1; ++i) {
    if (Check(p, vert[i], vert[i + 1])) {
      counter = 1;
    }
  }
  if (Check(p, vert[n - 1], vert[0])) {
    counter = 1;
  }
  for (int i = 0; i < n; ++i) {
    if (p.x == vert[i].x && p.y == vert[i].y) {
      counter = 1;
    }
  }
  if (counter == 1) {
    std::cout << "YES";
  } else {
    for (int i = 0; i < n - 1; ++i) {
      if (Cross(vert[i], vert[i + 1], p, hor) ||
          ((vert[i].x == vert[i + 1].x) && (p.x <= vert[i].x) && (p.y <= std::max(vert[i].y, vert[i + 1].y)) &&
           (p.y >= std::min(vert[i].y, vert[i + 1].y)))) {
        if (vert[i].y == vert[i + 1].y) {
        } else if (p.y == std::max(vert[i].y, vert[i + 1].y)) {
          ++counter;
        } else if (p.y != vert[i].y && p.y != vert[i + 1].y) {
          ++counter;
        }
      }
    }
    if (Cross(vert[n - 1], vert[0], p, hor) ||
        ((vert[n - 1].x == vert[0].x) && (p.x <= vert[n - 1].x) && (p.y <= std::max(vert[n - 1].y, vert[0].y)) &&
         (p.y >= std::min(vert[n - 1].y, vert[0].y)))) {
      if (vert[n - 1].y == vert[0].y) {
      } else if (p.y == std::max(vert[n - 1].y, vert[0].y)) {
        ++counter;
      } else if (p.y != vert[n - 1].y && p.y != vert[0].y) {
        ++counter;
      }
    }

    if (counter % 2 == 0) {
      std::cout << "NO";
    } else {
      std::cout << "YES";
    }
  }
  delete[] vert;
}