#include <iostream>

int main() {
  char array[100000];
  int i = 0;
  while (true) {
    std::cin >> array[i];
    if (array[i] == '#') {
      break;
    }
    ++i;
  }
  int n = i;
  if (n == 1) {
    std::cout << array[0];
  } else if (n % 2 != 0) {
    for (int i = 0; i < n; i = i + 2) {
      std::cout << array[i];
    }
    for (int i = n - 2; i > 0; i = i - 2) {
      std::cout << array[i];
    }
  } else {
    for (int i = 0; i < n; i = i + 2) {
      std::cout << array[i];
    }
    for (int i = n - 1; i > 0; i = i - 2) {
      std::cout << array[i];
    }
  }
}