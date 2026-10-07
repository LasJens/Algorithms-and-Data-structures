#include <iostream>
#include <vector>

template <class T, class Compare = std::equal_to<T> >
class Prefix{
 public:
  template <std::random_access_iterator Iter>
  Prefix(Iter begin, Iter end, Compare compare = Compare()) : compare_(compare), prefix_(std::distance(begin, end)){
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
  void print() {
    for (auto i : prefix_) {
      std::cout << i << ' ';
    }
  }
 private:
  Compare compare_;
  std::vector <size_t> prefix_;
};

/* int main() {
  std::string example = "abaaabab";
  Prefix<char> prefix(example.begin(), example.end());
  prefix.print();
} */