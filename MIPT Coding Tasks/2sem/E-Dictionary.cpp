#include <iostream>
#include <algorithm>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::unordered_map<std::string, std::string> dict1;
  std::unordered_map<std::string, std::string> dict2;
  for (int i = 0; i < n; ++i) {
    std::string word;
    std::string syn;
    std::cin >> word >> syn;
    dict1[word] = syn;
    dict2[syn] = word;
  }
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    std::string word;
    std::cin >> word;
    if (dict1.find(word) != dict1.end()) {
      std::cout << dict1[word] << '\n';
    } else if (dict2.find(word) != dict2.end()) {
      std::cout << dict2[word] << '\n';
    }
  }
}