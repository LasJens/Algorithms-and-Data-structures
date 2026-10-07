#include <iostream>
#include <string>
#include <vector>

template <class T, class Compare = std::equal_to<T> >
class Prefix {
 public:
  Compare compare_;
  std::vector<size_t> prefix_;
  template <std::random_access_iterator Iter>
  Prefix(Iter begin, Iter end, Compare compare = Compare()) : compare_(compare), prefix_(std::distance(begin, end)) {
    prefix_[0] = 0;
    for (size_t i = 1; i < prefix_.size(); ++i) {
      size_t prev = prefix_[i - 1];
      while (prev > 0 && !compare_(begin[prev], begin[i])) {
        prev = prefix_[prev - 1];
      }
      if (compare_(begin[prev], begin[i])) {
        ++prev;
      }
      prefix_[i] = prev;
    }
  }
  void Print() {
    for (auto i : prefix_) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  std::string s1;
  std::cin >> s1;
  for (int i = 1; i < n; ++i) {
    std::string cur;
    std::cin >> cur;
    std::string couple;
    if (s1.size() > cur.size()) {
      std::string assist(cur.size(), 0);
      for (size_t j = 0; j < assist.size(); ++j) {
        assist[j] = s1[s1.size() - cur.size() + j];
      }
      couple = cur + '#' + assist;
    } else {
      couple = cur + '#' + s1;
    }
    Prefix<char> prefix(couple.begin(), couple.end());
    s1 += cur.substr(prefix.prefix_[couple.size() - 1]);
  }
  std::cout << s1;
}