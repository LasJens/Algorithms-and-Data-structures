#include <iostream>
#include <cmath>
#include <iomanip>

struct Line {
  double a = 0;
  double b = 0;
  double c = 0;
};

int main() {
  std::cout << std::setprecision(15);
  Line n;
  Line m;
  std::cin >> n.a >> n.b >> n.c;
  std::cin >> m.a >> m.b >> m.c;
  std::cout << n.b << " " << -n.a << '\n';
  std::cout << m.b << " " << -m.a << '\n';
  if (n.a * m.b - n.b * m.a == 0) {
    if (n.a == 0) {
      std::cout << std::abs(n.c / n.b - m.c / m.b);
    } else if (n.b == 0) {
      std::cout << std::abs(n.c / n.a - m.c / m.a);
    } else {
      double y = -m.c / m.b;
      double r = (n.b * y + n.c) / std::sqrt(n.a * n.a + n.b * n.b);
      std::cout << r;
    }
  } else {
    double x = (n.b * m.c - m.b * n.c) / (n.a * m.b - m.a * n.b);
    double y = -(n.a * m.c - m.a * n.c) / (n.a * m.b - m.a * n.b);
    std::cout << x << " " << y;
  }
}