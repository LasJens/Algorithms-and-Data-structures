#include <iostream>
#include <algorithm>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  auto array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  int m = 0;
  std::cin >> m;
  auto array2 = new int[m];
  for (int i = 0; i < m; ++i) {
    std::cin >> array2[i];
  }
  for (int i = 0; i < m; ++i) {
    auto a = std::lower_bound(array, array + n, array2[i]);
    auto b = std::upper_bound(array, array + n, array2[i]);
    std::cout << b - a << " ";
  }
  delete[] array;
  delete[] array2;
}