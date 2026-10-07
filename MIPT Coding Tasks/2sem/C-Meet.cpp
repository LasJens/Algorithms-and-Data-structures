#include <iostream>
#include <algorithm>
#include <vector>

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
  std::cout << std::count(input.begin(), input.end(), m);
}