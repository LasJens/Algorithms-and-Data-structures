#include <iostream>

void PrintLcs(int* arr_1, int* arr_2, int**& plcs, int i, int j) {
  if (i == 0 || j == 0) {
    return;
  }
  if (plcs[i][j] == 0) {
    PrintLcs(arr_1, arr_2, plcs, i - 1, j - 1);
    std::cout << arr_1[i] << " ";
  } else {
    if (plcs[i][j] == 1) {
      PrintLcs(arr_1, arr_2, plcs, i - 1, j);
    } else {
      PrintLcs(arr_1, arr_2, plcs, i, j - 1);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  int arr_1[1001];
  int arr_2[1001];
  std::cin >> n;
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> arr_1[i];
  }
  std::cin >> m;
  for (int i = 1; i < m + 1; ++i) {
    std::cin >> arr_2[i];
  }
  int lcs[1001][1001];
  auto plcs = new int*[n + 1];
  for (int i = 0; i < n + 1; ++i) {
    plcs[i] = new int[m + 1];
  }
  lcs[0][0] = 0;
  for (int i = 1; i < n + 1; ++i) {
    lcs[i][0] = 0;
  }
  for (int i = 1; i < m + 1; ++i) {
    lcs[0][i] = 0;
  }
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      if (arr_1[i] == arr_2[j]) {
        lcs[i][j] = lcs[i - 1][j - 1] + 1;
        plcs[i][j] = 0;
      } else {
        if (lcs[i - 1][j] >= lcs[i][j - 1]) {
          lcs[i][j] = lcs[i - 1][j];
          plcs[i][j] = 1;
        } else {
          lcs[i][j] = lcs[i][j - 1];
          plcs[i][j] = 2;
        }
      }
    }
  }
  PrintLcs(arr_1, arr_2, plcs, n, m);
  for (int i = 0; i < n + 1; ++i) {
    delete[] plcs[i];
  }
  delete[] plcs;
}
