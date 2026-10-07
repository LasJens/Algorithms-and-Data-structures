#include <iostream>

int main() {
  int64_t w, h, n;
  std::cin >> w >> h >> n;
  int64_t l_max = 0;
  if (w > h) {
    l_max = w * n;
  } else {
    l_max = h * n;
  }
  int64_t left = 0, right = l_max, value = (left + right) / 2;
  while (left < right - 1) {
    if ((value / w) * (value / h) >= n) {
      right = value;
    } else {
      left = value;
    }
    value = (right + left) / 2;
  }
  if ((value / w) * (value / h) >= n) {
    std::cout << value;
  } else {
    std::cout << value + 1;
  }
}