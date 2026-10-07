#include <iostream>

int main() {
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  int k = 0;
  std::cin >> k;
  char str[1000003];
  str[0] = '0';
  int i = 1;
  while (str[i - 1] != '2') {
    std::cin >> str[i];
    ++i;
  }
  int ptr = 1;
  int k_ptr = 1;
  char current = str[1];
  if (str[1] == '1') {
    std::cout << '0' << " ";
  }
  while (str[ptr] != '2') {
    while (k_ptr <= k && str[ptr] == current) {
      k_ptr++;
      ptr++;
    }
    if (k_ptr == k + 1 && str[ptr] == current) {
      std::cout << k << " " << '0' << " ";
      k_ptr = 1;
    } else if (k_ptr == k + 1 && str[ptr] != current) {
      std::cout << k << " ";
      k_ptr = 1;
      current = str[ptr];
    } else {
      std::cout << k_ptr - 1 << " ";
      k_ptr = 1;
      current = str[ptr];
    }
  }
}