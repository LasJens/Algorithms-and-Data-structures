#include <iostream>
#include <vector>
#include <string>

int main() {
  std::string p;
  std::string t;
  std::cin >> p >> t;
  std::vector<bool> ans(t.size() + 2, false);
  int counter = 0;
  auto p_size = static_cast<int64_t>(p.size());
  auto t_size = static_cast<int64_t>(t.size());
  for (int64_t i = 0; i <= t_size - p_size; ++i) {
    int mistake = 0;
    for (int64_t j = 0; j < p_size; ++j) {
      if (t[i + j] != p[j]) {
        ++mistake;
      }
      if (mistake == 2) {
        break;
      }
    }
    if (mistake < 2) {
      ans[i + 1] = true;
      ++counter;
    }
  }
  std::cout << counter << '\n';
  for (size_t i = 0; i < ans.size(); ++i) {
    if (ans[i]) {
      std::cout << i << ' ';
    }
  }
}