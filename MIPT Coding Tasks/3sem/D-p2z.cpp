#include <iostream>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> zet(n, 0);
  std::vector<int> prefix(n, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> prefix[i];
  }

  for (int i = 1; i < n; i++) {
    if (prefix[i] > 0) {
      zet[i - prefix[i] + 1] = prefix[i];
    }
  }
  zet[0] = n;
  int i = 1;
  while (i < n) {
    int t = i;
    if (zet[i] > 0) {
      for (int j = 1; j < zet[i]; ++j) {
        if (zet[i + j] > zet[j]) {
          break;
        }
        zet[i + j] = std::min(zet[j], zet[i] - j);
        t = i + j;
      }
    }
    i = t + 1;
  }

  for (int i = 0; i < n; ++i) {
    std::cout << zet[i] << " ";
  }
}