#include <iostream>

void PutFerz(int array[10][10], int n, int& counter) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (array[i][j] == 0) {
        for (int k = 0; k < n; ++k) {
          array[i][k] = 2;
        }
        for (int k = 0; k < n; ++k) {
          array[k][j] = 2;
        }
        for (int k = 0; ((i + k) < n) and ((j + k) < n); ++k) {
          array[i + k][j + k] = 2;
        }
        for (int k = 0; ((i - k) > 0) and ((j - k) > 0); ++k) {
          array[i - k][j - k] = 2;
        }
        for (int k = 0; ((i - k) > 0) and ((j + k) < n); ++k) {
          array[i - k][j + k] = 2;
        }
        for (int k = 0; ((i + k) < n) and ((j - k) > 0); ++k) {
          array[i + k][j - k] = 2;
        }
        array[i][j] = 1;
        ++counter;
        return;
      }
    }
  }
}

int main() {
  int array[10][10];
  int sum = 0;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      array[i][j] = 0;
    }
  }
  int counter = 0;
  while (counter < 8) {
    int copy_array[10][10];
    int copy_counter = counter;
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        copy_array[i][j] = array[i][j];
      }
    }
    PutFerz(array, 10, counter);
    int flag = 0;
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        if (array[i][j] == 0) {
          flag = 1;
          break;
        }
      }
      if (flag == 1) {
        break;
      }
    }
    if (flag == 0 and counter != 10) {
      for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
          array[i][j] = copy_array[i][j];
        }
      }
      int flag = 0;
      for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
          if (array[i][j] == 0) {
            array[i][j] = 2;
            flag = 1;
            break;
          }
        }
        if (flag == 1) {
          break;
        }
      }
      counter--;
      PutFerz(array, 10, counter);
    }
  }
  std::cout << counter << "\n";
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      std::cout << array[i][j] << " ";
    }
    std::cout << "\n";
  }
}
