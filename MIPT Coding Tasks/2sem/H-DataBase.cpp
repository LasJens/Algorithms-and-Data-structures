#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::vector<std::string> data;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
      data.push_back(word);
    }
  }
  std::unordered_set<std::string> names;
  for (size_t i = 0; i < data.size(); i = i + 3) {
    names.insert(data[i]);
  }
  std::vector<std::string> names2;
  for (size_t i = 0; i < names.size(); ++i) {
    auto it = names.begin();
    std::advance(it, i);
    names2.push_back(*it);
  }
  std::sort(names2.begin(), names2.end());
  std::map<std::string, std::map<std::string, size_t> > list;
  for (size_t i = 0; i < data.size(); i = i + 3) {
    list[data[i]][data[i + 1]] += std::stoi(data[i + 2]);
  }
  for (const auto& name : names2) {
    std::cout << name << ":\n";
    for (const auto& entry : list[name]) {
      std::cout << entry.first << " " << entry.second << '\n';
    }
  }
}