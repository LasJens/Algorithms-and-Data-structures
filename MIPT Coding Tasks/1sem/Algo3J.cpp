#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  auto array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  auto res = new int[5001];
  for (int i = 0; i < 5001; ++i) {
    res[i] = 0;
  }
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < array[i]; ++j) {
      res[array[i]] = res[array[i]] + res[j];
    }
    res[array[i]] += 1;
    res[array[i]] = res[array[i]] % 1000000;
  }
  for (int i = 0; i < 5001; ++i) {
    sum += res[i];
  }
  std::cout << sum % 1000000;
  delete[] array;
  delete[] res;
}