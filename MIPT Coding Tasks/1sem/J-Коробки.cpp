#include <iostream>

struct Box {
  size_t height;
  size_t width;
};

int main() {
  int n = 0;
  std::cin >> n;
  size_t counter = 0;
  auto array = new Box[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i].height >> array[i].width;
    if (array[i].height > array[i].width) {
      counter += array[i].height;
    } else {
      counter += array[i].width;
    }
  }
  std::cout << counter;
  delete[] array;
}