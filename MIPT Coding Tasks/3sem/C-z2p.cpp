#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> zet(n, 0);
  std::vector<int> prefix(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> zet[i];
  }
  zet[0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = zet[i] - 1; j >= 0; --j) {
      if (prefix[i + j] > 0) {
        break;
      }
      prefix[i + j] = j + 1;
    }
  }
  for (int i = 0; i < n; ++i) {
    std::cout << prefix[i] << " ";
  }
}