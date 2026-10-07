#include <iostream>
#include <algorithm>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::unordered_map<std::string, int> bank;
  for (int i = 0; i < n; ++i) {
    int command = 0;
    std::cin >> command;
    if (command == 1) {
      std::string name;
      std::cin >> name;
      int sum = 0;
      std::cin >> sum;
      bank[name] += sum;
    } else {
      std::string name;
      std::cin >> name;
      if (bank.find(name) != bank.end()) {
        std::cout << bank[name] << '\n';
      } else {
        std::cout << "ERROR" << '\n';
      }
    }
  }
}