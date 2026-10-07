#include <iostream>

int main() {
  char array[255];
  for (int i = 0; i < 255; ++i) {
    array[i] = '\0';
  }
  std::cin.getline(array, 255);
  
}



std::ios_base::sync_with_stdio(false);
std::cin.tie(0);
std::cout.tie(0);