#include <iostream>
#include <cmath>
#include <iomanip>

struct Vector {
  double xs = 0;
  double ys = 0;
  double xf = 0;
  double yf = 0;
};

int main() {
  std::cout << std::setprecision(15);
  Vector a;
  Vector b;
  std::cin >> a.xs >> a.ys >> a.xf >> a.yf;
  std::cin >> b.xs >> b.ys >> b.xf >> b.yf;
  std::cout << std::sqrt(std::pow((a.xs - a.xf), 2) + std::pow((a.ys - a.yf), 2)) << " ";
  std::cout << std::sqrt(std::pow((b.xs - b.xf), 2) + std::pow((b.ys - b.yf), 2)) << '\n';
  std::cout << a.xf - a.xs + b.xf - b.xs << " ";
  std::cout << a.yf - a.ys + b.yf - b.ys << '\n';
  std::cout << (a.xf - a.xs) * (b.xf - b.xs) + (a.yf - a.ys) * (b.yf - b.ys) << " ";
  std::cout << (a.xf - a.xs) * (b.yf - b.ys) - (a.yf - a.ys) * (b.xf - b.xs) << '\n';
  std::cout << std::abs((a.xf - a.xs) * (b.yf - b.ys) - (a.yf - a.ys) * (b.xf - b.xs)) / 2 << '\n';
}