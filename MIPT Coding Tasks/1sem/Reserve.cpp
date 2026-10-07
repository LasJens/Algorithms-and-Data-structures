#include <iostream>
#include <algorithm>

void LIS(int* array, int* prev, int max_idx) {
  int pos = max_idx;
  auto lis = new int[pos];
  int index = 0;
  while (pos != -1) {
    lis[index] = array[pos];
    pos = prev[pos];
    index++;
  }
  std::cout << lis[4] << " ";
  for (int i = index - 1; i >= 0; i--) {
    std::cout << lis[i] << " ";
  }
  delete[] lis;
}

void FindLISLen(int* array, int n) {
  auto prev = new int[n];
  auto dp = new int[n]();
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    prev[i] = -1;
  }
  for (int i = 0; i < n; i++) {
    dp[i] = 1;
    prev[i] = -1;
    for (int j = 0; j < i; j++) {
      if (array[j] < array[i] && dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1;
        prev[i] = j;
      }
    }
  }
  int max_dp = -1;
  int max_idx = -1;
  for (int i = 0; i < n; i++) {
    if (max_dp < dp[i]) {
      max_dp = dp[i];
      max_idx = i;
    }
  }
  LIS(array, prev, max_idx);
  delete[] prev;
  delete[] dp;
}

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> array[i];
  }
  FindLISLen(array, n);
  delete[] array;
  return 0;
}