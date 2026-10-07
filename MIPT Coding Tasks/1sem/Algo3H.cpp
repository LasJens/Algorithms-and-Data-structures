#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  auto prev = new int[n];
  for (int i = 0; i < n; ++i) {
    prev[i] = -1;
  }
  auto dp = new int[n];
  for (int i = 0; i < n; ++i) {
    dp[i] = 0;
  }
  dp[0] = 1;
  for (int i = 0; i < n; ++i) {
    dp[i] = 1;
    prev[i] = -1;
    for (int j = 0; j < i; ++j) {
      if (array[j] < array[i] && dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1;
        prev[i] = j;
      }
    }
  }
  int max_index = 0;
  for (int i = 0; i < n; ++i) {
    if (dp[i] > dp[max_index]) {
      max_index = i;
    }
  }
  auto lis = new int[max_index];
  int i = 0;
  while (max_index != -1) {
    lis[i] = array[max_index];
    max_index = prev[max_index];
    ++i;
  }
  for (int j = i - 1; j >= 0; --j) {
    std::cout << lis[j] << " ";
  }
  delete[] array;
  delete[] prev;
  delete[] dp;
  delete[] lis;
}