#include <iostream>
#include <cmath>
#include <iomanip>

struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

int main() {
  std::cout << std::setprecision(15);
  int n = 0;
  std::cin >> n;
  auto vert = new Point[n];
  auto array = new int[n];
  bool flag = true;
  for (int i = 0; i < n; ++i) {
    std::cin >> vert[i].x >> vert[i].y;
  }
  int64_t v = 0;
  for (int i = 0; i < n - 2; ++i) {
    v = (vert[i + 1].x - vert[i].x) * (vert[i + 2].y - vert[i + 1].y) -
        (vert[i + 1].y - vert[i].y) * (vert[i + 2].x - vert[i + 1].x);
    if (v > 0) {
      array[i] = 1;
    } else if (v == 0) {
      array[i] = 0;
    } else {
      array[i] = -1;
    }
  }
  v = (vert[n - 1].x - vert[n - 2].x) * (vert[0].y - vert[n - 1].y) -
      (vert[n - 1].y - vert[n - 2].y) * (vert[0].x - vert[n - 1].x);
  if (v > 0) {
    array[n - 2] = 1;
  } else if (v == 0) {
    array[n - 2] = 0;
  } else {
    array[n - 2] = -1;
  }
  v = (vert[0].x - vert[n - 1].x) * (vert[1].y - vert[0].y) - (vert[0].y - vert[n - 1].y) * (vert[1].x - vert[0].x);
  if (v > 0) {
    array[n - 1] = 1;
  } else if (v == 0) {
    array[n - 1] = 0;
  } else {
    array[n - 1] = -1;
  }
  int i = 0;
  while (array[i] == 0) {
    ++i;
  }
  int factor = array[i];
  for (int i = 0; i < n; ++i) {
    if (array[i] != 0 && array[i] != factor) {
      flag = false;
      std::cout << "NO";
      break;
    }
  }
  if (flag) {
    std::cout << "YES";
  }
  delete[] vert;
}