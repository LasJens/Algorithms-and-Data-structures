#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  int a = 1000000;
  auto dp = new int[n + 1];
  for (int i = 1; i < n + 1; ++i) {
    dp[i] = a;
  }
  for (int i = 0; i < n; ++i) {
    int left = 0;
    int right = n;
    while (right - left > 1) {
      int mid = (left + right) / 2;
      if (dp[mid] >= array[i]) {
        right = mid;
      } else {
        left = mid;
      }
    }
    dp[right] = array[i];
  }
  int counter = 0;
  while (counter < n + 1 && dp[counter] != a) {
    ++counter;
  }
  std::cout << counter - 1;
  delete[] dp;
  delete[] array;
}