#include <iostream>

size_t Fact(size_t x) {
  size_t ans = 1;
  while (x > 0) {
    ans = ans * x;
    x = x - 1;
  }
  return ans;
}

size_t Deg(size_t n) {
  size_t ans = 1;
  while (n > 0) {
    ans *= 2;
    n--;
  }
  return ans;
}

int main() {
  int n = 0;
  std::cin >> n;
  size_t quantity = 0;
  for (int i = 0; i < (n + 1) / 2 + 1; ++i) {
    int between_a = i - 1;
    if (between_a < 0) {
      between_a = 0;
    }
    quantity += Fact(n - between_a) / Fact(i) / Fact(n - between_a - i) * Deg(n - i);
  }
  std::cout << quantity;
}
