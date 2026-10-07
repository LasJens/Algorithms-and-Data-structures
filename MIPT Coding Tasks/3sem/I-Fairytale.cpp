#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> vec(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> vec[i];
  }
  std::vector<int> p(n, 0);
  int left = 0;
  int right = 0;
  for (int i = 1; i < n; ++i) {
    if (i <= right) {
      p[i] = std::min(right - i + 1, p[right + left - i + 1]);
    }
    while ((i + p[i] < n) && (i - p[i] > 0) && (vec[i + p[i]] == vec[i - p[i] - 1])) {
      ++p[i];
    }
    if (i + p[i] - 1 > right) {
      right = i + p[i] - 1;
      left = i - p[i];
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    if (p[i] == i) {
      std::cout << n - p[i] << ' ';
    }
  }
}