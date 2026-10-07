#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int*[n + 1];
  for (int i = 0; i < n + 1; ++i) {
    array[i] = new int[n + 1];
  }
  for (int i = 0; i < n + 1; ++i) {
    for (int j = 0; j < n + 1; ++j) {
      array[i][j] = 0;
    }
  }
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < n + 1; ++j) {
      if (i >= j) {
        array[i][j] = (array[i - j][j] + array[i - j][j - 1]) % 1000000007;
      } else {
        array[i][j] = (array[0][j] + array[0][j - 1]) % 1000000007;
      }
    }
  }
  int ans = 0;
  for (int i = 1; i < n + 1; ++i) {
    ans += array[n][i];
  }
  std::cout << ans;
  for (int i = 0; i < n + 1; ++i) {
    delete[] array[i];
  }
  delete[] array;
}