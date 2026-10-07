#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <sstream>

struct Compare {
  bool operator()(std::pair<int, std::string> a, std::pair<int, std::string> b) const {
    if (a.first == b.first) {
      return a.second < b.second;
    }
    return a.first > b.first;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::vector<std::string> poem;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
      poem.push_back(word);
    }
  }
  std::unordered_map<std::string, int> list;
  for (size_t i = 0; i < poem.size(); ++i) {
    ++list[poem[i]];
  }
  std::vector<std::pair<int, std::string> > dict;
  for (auto it = list.begin(); it != list.end(); ++it) {
    auto key = it->first;
    auto value = it->second;
    dict.emplace_back(value, key);
  }
  std::sort(dict.begin(), dict.end(), Compare());
  for (size_t i = 0; i < dict.size(); ++i) {
    std::cout << dict[i].second << '\n';
  }
}