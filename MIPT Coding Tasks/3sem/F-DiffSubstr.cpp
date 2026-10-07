#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Compare {
  bool operator()(std::pair<std::string, size_t> s1, std::pair<std::string, size_t> s2) const {
    return s1.first < s2.first;
  }
};

int main() {
  std::string s;
  std::cin >> s;
  if (s.size() == 1) {
    std::cout << 1;
  } else {
    std::vector<std::pair<std::string, size_t> > vec(s.size());
    vec[s.size() - 1].first = s[s.size() - 1];
    vec[s.size() - 1].second = s.size() - 1;
    vec[0].first = s;
    vec[0].second = 0;
    for (size_t i = s.size() - 2; i > 0; --i) {
      vec[i].first = s[i] + vec[i + 1].first;
      vec[i].second = i;
    }
    std::sort(vec.begin(), vec.end());

    std::vector<size_t> r(s.size(), 0);
    for (size_t i = 0; i < s.size(); ++i) {
      r[vec[i].second] = i;
    }

    std::vector<size_t> lcp(s.size(), 0);
    size_t k = 0;
    for (size_t j = 0; j < s.size(); ++j) {
      size_t i = r[j];
      if (i == 0) {
        k = 0;
        continue;
      }
      if (k > 0) {
        k -= 1;
      }
      while (s[vec[i].second + k] == s[vec[i - 1].second + k]) {
        k += 1;
      }
      lcp[i] = k;
    }

    size_t ans = s.size() - vec[0].second;
    for (size_t i = 1; i < s.size(); ++i) {
      ans += (s.size() - vec[i].second - lcp[i]);
    }
    std::cout << ans;
  }
}