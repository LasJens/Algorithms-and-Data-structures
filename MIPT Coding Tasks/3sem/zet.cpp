#include <iostream>
#include <vector>

template <class T, class Compare = std::equal_to<T> >
class ZetFunction{
 public:
  template <std::random_access_iterator Iter>
  ZetFunction(Iter begin, Iter end, Compare compare = Compare()) : compare_(compare), z_(std::distance(begin, end)){
    size_t left_boarder = 0;
    size_t right_boarder = 0;
    for (size_t i = 1; i < z_.size(); ++i) {
      if (i <= right_boarder) {
        z_[i] = std::min(right_boarder - i + 1, z_[i - left_boarder]);
      }
      while((i + z_[i] < z_.size()) && (compare_(begin[z_[i]], begin[i + z_[i]]))) {
        ++z_[i];
      }
      if (i + z_[i] - 1 > right_boarder) {
        left_boarder = i;
        right_boarder = z_[i] + i - 1;
      }
    }
  }
  void print() {
    for (auto i : z_) {
      std::cout << i << ' ';
    }
  }
 private:
  Compare compare_;
  std::vector <size_t> z_;
};

/* int main() {
  std::string example = "abacaba";
  ZetFunction<char> zet(example.begin(), example.end());
  zet.print();
} */