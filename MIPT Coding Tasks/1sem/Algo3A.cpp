#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  size_t array[91];
  array[1] = 2;
  array[2] = 3;
  for (int i = 3; i <= n; ++i) {
    array[i] = array[i - 1] + array[i - 2];
  }
  std::cout << array[n];
}