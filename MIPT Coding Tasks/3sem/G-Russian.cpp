#include <iostream>
#include <vector>
#include <string>

template <class T, class Compare = std::equal_to<T> >
class ZetFunction {
 public:
  Compare compare_;
  std::vector<size_t> z_;
  template <std::random_access_iterator Iter>
  ZetFunction(Iter begin, Iter end, Compare compare = Compare()) : compare_(compare), z_(std::distance(begin, end)) {
    size_t left_boarder = 0;
    size_t right_boarder = 0;
    for (size_t i = 1; i < z_.size(); ++i) {
      if (i <= right_boarder) {
        z_[i] = std::min(right_boarder - i + 1, z_[i - left_boarder]);
      }
      while ((i + z_[i] < z_.size()) && (compare_(begin[z_[i]], begin[i + z_[i]]))) {
        ++z_[i];
      }
      if (i + z_[i] - 1 > right_boarder) {
        left_boarder = i;
        right_boarder = z_[i] + i - 1;
      }
    }
  }
  void Print() {
    for (auto i : z_) {
      std::cout << i << ' ';
    }
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  std::string a(n - 1, 0);
  std::string b(n - 1, 0);
  std::cin >> a >> b;
  std::string s0 = a + '#' + b + '0' + b;
  std::string s1 = a + '#' + b + '1' + b;
  ZetFunction<char> zet0(s0.begin(), s0.end());
  ZetFunction<char> zet1(s1.begin(), s1.end());
  std::pair<int, bool> flag;
  flag.first = 0;
  flag.second = false;
  for (size_t i = a.size() + 1; i < s0.size(); ++i) {
    if (zet0.z_[i] == a.size()) {
      ++flag.first;
      flag.second = true;
      break;
    }
  }
  for (size_t i = a.size() + 1; i < s0.size(); ++i) {
    if (zet1.z_[i] == a.size()) {
      ++flag.first;
      break;
    }
  }
  if (flag.first == 2) {
    std::cout << "Random";
  } else if (flag.second) {
    std::cout << "No";
  } else {
    std::cout << "Yes";
  }
}