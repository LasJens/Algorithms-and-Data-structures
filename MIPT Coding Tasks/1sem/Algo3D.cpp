#include <iostream>

int main() {
  int m = 0;
  int n = 0;
  std::cin >> m >> n;
  size_t array[16][51];
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      array[i][j] = 0;
    }
  }
  array[1][1] = 1;
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      if (i < n && j < m) {
        array[i + 1][j + 1] += array[i][j];
      }
      if (i < n) {
        array[i + 1][j] += array[i][j];
      }
      if (j < m) {
        array[i][j + 1] += array[i][j];
      }
    }
  }
  std::cout << array[n][m];
  return 0;
}