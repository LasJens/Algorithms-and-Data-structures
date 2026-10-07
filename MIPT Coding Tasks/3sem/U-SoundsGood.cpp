#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <memory>

class Trie {
 public:
  Trie() {
    root_ = std::make_shared<Node>();
  }

  void Add(const std::string& word, int64_t ind) {
    Node* node = root_.get();
    auto len = static_cast<int64_t>(word.length());
    for (auto i = len - 1; i >= 0; --i) {
      if (IsPalindrome(word, 0, i)) {
        node->pal_suff.push_back(ind);
      }
      char c = word[i];
      auto& next_node = node->to[c];
      if (!next_node) {
        node->to[c] = std::make_shared<Node>();
      }
      node = node->to[c].get();
    }
    node->index = ind;
    node->pal_suff.push_back(ind);
  }

  void Find(const std::string& word, int64_t ind, std::vector<std::pair<int64_t, int64_t> >& ans) {
    Node* node = root_.get();
    auto len = static_cast<int64_t>(word.size());
    for (int64_t i = 0; i < len; ++i) {
      if (node->index != -1 && node->index != ind && IsPalindrome(word, i, len - 1)) {
        ans.emplace_back(ind + 1, node->index + 1);
      }
      char c = word[i];
      auto it = node->to.find(c);
      if (it == node->to.end()) {
        return;
      }
      node = it->second.get();
    }
    for (int64_t pal_index : node->pal_suff) {
      if (ind != pal_index) {
        ans.emplace_back(ind + 1, pal_index + 1);
      }
    }
  }

  bool IsPalindrome(const std::string& word, int64_t left, int64_t right) {
    while (left < right) {
      if (word[left] != word[right]) {
        return false;
      }
      ++left;
      --right;
    }
    return true;
  }

 private:
  struct Node {
    std::unordered_map<char, std::shared_ptr<Node> > to;
    int64_t index = -1;
    std::vector<int64_t> pal_suff;
  };
  std::shared_ptr<Node> root_;
};

int main() {
  int64_t n = 0;
  std::cin >> n;
  std::string word;
  std::vector<std::string> words(n);
  Trie trie;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> word;
    words[i] = word;
    trie.Add(word, i);
  }
  std::vector<std::pair<int64_t, int64_t> > ans;
  for (int64_t i = 0; i < n; ++i) {
    trie.Find(words[i], i, ans);
  }
  std::cout << ans.size() << '\n';
  for (const auto& pair : ans) {
    std::cout << pair.first << " " << pair.second << '\n';
  }
}