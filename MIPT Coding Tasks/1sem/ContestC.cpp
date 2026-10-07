#include <iostream>

int main() {
  int t = 0;
  std::cin >> t;
  for (int i = 0; i < t; ++i) {
    size_t n = 0;
    size_t k = 0;
    std::cin >> n;
    std::cin >> k;
    if (n % (k + 1) == 0) {
      std::cout << "Artur\n";
    } else {
      std::cout << "Pasha\n";
    }
  }
}