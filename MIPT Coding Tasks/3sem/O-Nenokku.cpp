#include <vector>
#include <iostream>
#include <string>

class SuffAuto {
 public:
  explicit SuffAuto() {
    t_.emplace_back();
  }

  explicit SuffAuto(const std::string& s) {
    t_.emplace_back();
    for (char c : s) {
      Add(c);
    }
  }

  void Print() const {
    std::cout << t_.size() << '\n';
    int64_t k = 0;
    for (const auto& node : t_) {
      for (size_t i = 0; i < node.to.size(); ++i) {
        if (node.to[i] != -1) {
          std::cout << k << ' ' << static_cast<char>('a' + i) << ' ' << node.to[i] << '\n';
        }
      }
      ++k;
    }
  }
  struct Node {
    int64_t len = 0;
    int64_t link = -1;
    std::vector<int64_t> to;

    Node() : to(26, -1) {
    }
  };

  int64_t last_ = 0;
  std::vector<Node> t_;

  void Add(char c) {
    t_.emplace_back();
    auto curr = static_cast<int64_t>(t_.size() - 1);
    int64_t p = last_;
    while (p != -1 && t_[p].to[c - 'a'] == -1) {
      t_[p].to[c - 'a'] = curr;
      p = t_[p].link;
    }
    t_[curr].len = t_[last_].len + 1;
    if (p == -1) {
      t_[curr].link = 0;
      last_ = curr;
      return;
    }
    auto q = t_[p].to[c - 'a'];
    if (t_[q].len == t_[p].len + 1) {
      t_[curr].link = q;
      last_ = curr;
      return;
    }
    t_.emplace_back();
    auto clone = static_cast<int64_t>(t_.size() - 1);
    t_[clone].len = t_[p].len + 1;
    while (p != -1 && t_[p].to[c - 'a'] == q) {
      t_[p].to[c - 'a'] = clone;
      p = t_[p].link;
    }
    t_[clone].to = t_[q].to;
    t_[clone].link = t_[q].link;
    t_[q].link = clone;
    t_[curr].link = clone;
    last_ = curr;
  }
  bool Find(const std::string& word) const {
    int64_t current_node = 0;
    for (char c : word) {
      if (t_[current_node].to[c - 'a'] == -1) {
        return false;
      }
      current_node = t_[current_node].to[c - 'a'];
    }
    return true;
  }
};

int main() {
  std::string type;
  std::string cur;
  SuffAuto automat;
  int j = 1;
  while (std::cin >> cur) {
    if (j % 2 == 1) {
      type = cur;
      ++j;
      continue;
    }
    for (size_t i = 0; i < cur.size(); ++i) {
      if ('A' <= cur[i] && cur[i] <= 'Z') {
        cur[i] = static_cast<char>(cur[i] + 32);
      }
    }
    if (type == "A") {
      for (size_t i = 0; i < cur.size(); ++i) {
        automat.Add(cur[i]);
      }
    } else {
      if (automat.Find(cur)) {
        std::cout << "YES";
      } else {
        std::cout << "NO";
      }
    }
    ++j;
  }
}