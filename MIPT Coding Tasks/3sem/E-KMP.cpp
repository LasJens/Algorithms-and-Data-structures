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
  std::string s;
  std::string p;
  std::cin >> s >> p;
  std::string s1;
  s1 = p + '#' + s;
  Prefix<char> prefix(s1.begin(), s1.end());
  for (size_t i = 0; i < s.size(); ++i) {
    if (prefix.prefix_[i + p.size() + 1] == p.size()) {
      std::cout << i + 1 - p.size() << '\n';
    }
  }
}