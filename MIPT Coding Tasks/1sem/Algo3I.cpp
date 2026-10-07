#include <iostream>
#include <cstring>

int Mark(char a, char b) {
  if (a == b) {
    return 0;
  }
  return 1;
}

size_t Minimum(size_t a, size_t b, size_t c) {
  if (a <= b && a <= c) {
    return a;
  }
  if (b <= a && b <= c) {
    return b;
  }
  return c;
}

int main() {
  auto s1 = new char[5000];
  auto s2 = new char[5000];
  std::cin.getline(s1, 5000);
  std::cin.getline(s2, 5000);
  size_t n = strlen(s1);
  size_t m = strlen(s2);
  auto dp = new size_t*[n + 1];
  for (size_t i = 0; i < n + 1; ++i) {
    dp[i] = new size_t[m + 1];
  }
  dp[0][0] = 0;
  for (size_t i = 1; i < n + 1; ++i) {
    dp[i][0] = i;
  }
  for (size_t i = 1; i < m + 1; ++i) {
    dp[0][i] = i;
  }
  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      dp[i][j] = Minimum(dp[i][j - 1] + 1, dp[i - 1][j] + 1, dp[i - 1][j - 1] + Mark(s1[i - 1], s2[j - 1]));
    }
  }
  std::cout << dp[n][m];
  delete[] s1;
  delete[] s2;
  for (size_t i = 0; i < n + 1; ++i) {
    delete[] dp[i];
  }
  delete[] dp;
}