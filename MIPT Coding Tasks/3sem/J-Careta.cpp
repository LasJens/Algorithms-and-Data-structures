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
  std::string a;
  std::string b;
  std::cin >> a >> b;
  std::string s = a + '#' + b;
  ZetFunction<char> zet(s.begin(), s.end());
  std::vector<std::string> prefix;
  bool flag = false;
  size_t marker = 0;
  if (zet.z_[a.size() + 1] == 0) {
    std::cout << "Yes";
  } else {
    marker = a.size() + 1;
    for (size_t i = a.size() + 1; i < s.size(); ++i) {
      if ((zet.z_[i] == 0) && i > marker - 1) {
        std::cout << "Yes";
        flag = true;
        break;
      }
      if (zet.z_[i] + i > marker) {
        if (marker != a.size() + 1) {
          prefix.push_back(a.substr(0, i - a.size() - 1));
        }
        marker = zet.z_[i] + i;
        if (marker >= s.size()) {
          prefix.push_back(a.substr(0, s.size() - i));
        }
      }
    }
  }
  if (!flag) {
    std::cout << "No" << '\n';
    for (size_t i = 0; i < prefix.size(); ++i) {
      std::cout << prefix[i] << ' ';
    }
  }
}