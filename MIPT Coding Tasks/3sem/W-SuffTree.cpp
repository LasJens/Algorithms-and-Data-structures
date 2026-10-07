#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

class SuffAuto {
 public:
  struct Node {
    int64_t len = 0;
    int64_t link = -1;
    int64_t end_pos = 0;
    std::map<char, int64_t> to;
  };
  std::vector<Node> t_;
  int64_t size_;
  int64_t last_;

  explicit SuffAuto() {
    t_.emplace_back();
  }

  explicit SuffAuto(const std::string& s) : t_(2 * s.size()), size_(0), last_(0) {
    t_.emplace_back();
    t_[0].end_pos = -1;
    for (auto c : s) {
      AddChar(c);
    }
  }

  void AddChar(char c) {
    ++size_;
    int64_t curr = size_;
    t_[curr].len = t_[last_].len + 1;
    t_[curr].end_pos = t_[last_].end_pos + 1;
    int64_t p = last_;
    while (p != -1 && t_[p].to.find(c) == t_[p].to.end()) {
      t_[p].to[c] = curr;
      p = t_[p].link;
    }
    if (p == -1) {
      t_[curr].link = 0;
      last_ = curr;
      return;
    }
    int64_t q = t_[p].to[c];
    if (t_[q].len == t_[p].len + 1) {
      t_[curr].link = q;
      last_ = curr;
      return;
    }
    ++size_;
    int64_t copy = size_;
    t_[copy].len = t_[p].len + 1;
    t_[copy].to = t_[q].to;
    t_[copy].end_pos = t_[q].end_pos;
    t_[copy].link = t_[q].link;
    while (p != -1 && t_[p].to[c] == q) {
      t_[p].to[c] = copy;
      p = t_[p].link;
    }
    t_[q].link = copy;
    t_[curr].link = copy;
    last_ = curr;
  }
};

struct Node2 {
  int64_t begin;
  int64_t len;
  std::map<char, int64_t> trns;
};

class SuffixTree : public SuffAuto {
 public:
  std::vector<Node2> Tree;
  int64_t size_;
  std::string str_;

  void ExtractTransitions(SuffAuto& sa, int64_t index) {
    int64_t suffix_index = sa.t_[index].link;
    if (suffix_index < 0 || suffix_index >= static_cast<int64_t>(Tree.size())) {
      return;
    }
    Tree[index].begin = static_cast<int64_t>(str_.size()) - sa.t_[index].end_pos + sa.t_[suffix_index].len - 1;
    Tree[index].len = sa.t_[index].len - sa.t_[suffix_index].len;
    Tree[suffix_index].trns[str_[Tree[index].begin]] = index;
  }

  explicit SuffixTree(const std::string& s) : str_(s) {
    std::string reversed(s);
    std::reverse(reversed.begin(), reversed.end());
    SuffAuto sa(reversed);
    size_ = sa.size_;
    Tree.resize(size_ + 1);
    Tree[0].begin = -1;
    Tree[0].len = 0;
    for (int64_t i = 1; i <= size_; i++) {
      ExtractTransitions(sa, i);
    }
  }
};

int main() {
  std::string str;
  std::cin >> str;
  SuffixTree suffix_tree(str + '#');
  std::cout << suffix_tree.size_ + 1 << '\n';
  for (int64_t i = 0; i <= suffix_tree.size_; i++) {
    for (auto it = suffix_tree.Tree[i].trns.begin(); it != suffix_tree.Tree[i].trns.end(); it++) {
      std::cout << i << ' ' << it->first << ' ' << suffix_tree.Tree[it->second].len << ' ' << it->second << '\n';
    }
  }
}
