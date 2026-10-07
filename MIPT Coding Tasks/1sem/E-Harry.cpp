#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n = 0;
  std::cin >> n;
  int x = 0;
  std::vector<int> vec;
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    vec.push_back(x);
  }
  int m = 0;
  std::cin >> m;
  std::cout << std::count(vec.begin(), vec.end(), m);
}