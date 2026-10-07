#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  size_t array[1000001];
  array[1] = 0;
  array[2] = 1;
  array[3] = 1;
  for (int i = 4; i <= n; ++i) {
    if (i % 2 == 0 && i % 3 == 0) {
      if (array[i - 1] <= array[i / 2] && array[i - 1] <= array[i / 3]) {
        array[i] = array[i - 1] + 1;
      } else if (array[i / 2] <= array[i / 3] && array[i / 2] <= array[i - 1]) {
        array[i] = array[i / 2] + 1;
      } else if (array[i / 3] <= array[i / 2] && array[i / 3] <= array[i - 1]) {
        array[i] = array[i / 3] + 1;
      }
    } else if (i % 2 == 0 && i % 3 != 0) {
      if (array[i - 1] <= array[i / 2]) {
        array[i] = array[i - 1] + 1;
      } else {
        array[i] = array[i / 2] + 1;
      }
    } else if (i % 2 != 0 && i % 3 == 0) {
      if (array[i - 1] <= array[i / 3]) {
        array[i] = array[i - 1] + 1;
      } else {
        array[i] = array[i / 3] + 1;
      }
    } else {
      array[i] = array[i - 1] + 1;
    }
  }
  std::cout << array[n];
}