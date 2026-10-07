#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  size_t ans = 1;
  for (size_t len = 1; len <= s.size() / 2; ++len) {
    for (size_t pos = 0; pos + len <= s.size(); ++pos) {
      size_t cur = 1;
      while (pos + len * cur < s.size() && s.substr(pos, len) == s.substr(pos + len * cur, len)) {
        ++cur;
      }
      ans = std::max(ans, cur);
      if (ans >= s.size() / len) {
        break;
      }
    }
  }
  std::cout << ans;
}