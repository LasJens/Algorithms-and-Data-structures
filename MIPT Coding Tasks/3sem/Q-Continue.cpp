#include <vector>
#include <iostream>

class SuffAuto {
 public:
  explicit SuffAuto() {
    t_.emplace_back();
  }

  explicit SuffAuto(const std::string& s) {
    t_.emplace_back();
    for (auto c : s) {
      Add(c);
    }
  }

 private:
  struct Node {
    int64_t len = 0;
    int64_t link = -1;
    std::vector<int64_t> to;
    Node() {
      to.assign(26, -1);
    }
  };

  int64_t last_ = 0;
  std::vector<Node> t_;
  int64_t distinct_count_ = 0;

  void Add(const char& c) {
    t_.emplace_back();
    auto cur = static_cast<int64_t>(t_.size() - 1);
    int64_t p = last_;
    while (p != -1 && t_[p].to[c - 'a'] == -1) {
      t_[p].to[c - 'a'] = cur;
      p = t_[p].link;
    }
    t_[cur].len = t_[last_].len + 1;
    if (p == -1) {
      t_[cur].link = 0;
    } else {
      auto q = t_[p].to[c - 'a'];
      if (t_[q].len == t_[p].len + 1) {
        t_[cur].link = q;
      } else {
        auto clone = static_cast<int64_t>(t_.size());
        t_.emplace_back();
        t_[clone].len = t_[p].len + 1;

        t_[clone].to = t_[q].to;
        t_[clone].link = t_[q].link;
        while (p != -1 && t_[p].to[c - 'a'] == q) {
          t_[p].to[c - 'a'] = clone;
          p = t_[p].link;
        }
        t_[q].link = clone;
        t_[cur].link = clone;
      }
    }
    last_ = cur;
    distinct_count_ += t_[cur].len - t_[t_[cur].link].len;
    std::cout << distinct_count_ << '\n';
  }
};

int main() {
  std::string s;
  std::cin >> s;
  SuffAuto suff(s);
}
