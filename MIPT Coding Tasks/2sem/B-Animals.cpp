#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> input;
  for (int i = 0; i < n; ++i) {
    int cur = 0;
    std::cin >> cur;
    input.push_back(cur);
  }
  int m = 0;
  std::cin >> m;
  std::vector<int> ask;
  for (int i = 0; i < m; ++i) {
    int color = 0;
    std::cin >> color;
    ask.push_back(color);
  }
  for (int i = 0; i < m; ++i) {
    auto a = std::lower_bound(input.begin(), input.end(), ask[i]);
    auto b = std::upper_bound(input.begin(), input.end(), ask[i]);
    std::cout << b - a << '\n';
  }
}