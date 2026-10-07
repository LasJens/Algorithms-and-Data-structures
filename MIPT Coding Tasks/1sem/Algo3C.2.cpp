#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;
  int array[21][10];
  for (int j = 0; j < 10; ++j) {
    array[1][j] = 1;
  }
  array[1][0] = 0;
  array[1][8] = 0;
  for (int i = 2; i < 21; ++i) {
    array[i][0] = array[i - 1][4] + array[i - 1][6];
    array[i][1] = array[i - 1][8] + array[i - 1][6];
    array[i][2] = array[i - 1][7] + array[i - 1][9];
    array[i][3] = array[i - 1][4] + array[i - 1][8];
    array[i][4] = array[i - 1][9] + array[i - 1][3] + array[i - 1][0];
    array[i][5] = 0;
    array[i][6] = array[i - 1][1] + array[i - 1][7] + array[i - 1][0];
    array[i][7] = array[i - 1][2] + array[i - 1][6];
    array[i][8] = array[i - 1][1] + array[i - 1][3];
    array[i][9] = array[i - 1][4] + array[i - 1][2];
  }
  int ans = 0;
  for (int i = 0; i < 10; ++i) {
    ans += array[n][i];
  }
  std::cout << ans;
}