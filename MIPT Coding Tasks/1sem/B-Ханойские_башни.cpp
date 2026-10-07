#include <iostream>

void RemoveTower(int n, int s_begin, int s_end) {
  if (n == 1) {
    std::cout << 1 << " " << s_begin << " " << s_end << "\n";
  } else {
    RemoveTower(n - 1, s_begin, 6 - s_begin - s_end);
    std::cout << n << " " << s_begin << " " << s_end << "\n";
    RemoveTower(n - 1, 6 - s_begin - s_end, s_end);
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  RemoveTower(n, 1, 3);
}