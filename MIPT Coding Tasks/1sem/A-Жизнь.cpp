#include <iostream>

int main() {

  int n = 0, t = 0;
  std::cin >> n >> t;

  //выделение памяти
  auto array = new int*[n];
  for (int i = 0; i < n; ++i) {
    array[i] = new int[n];
  }
  auto copy_array = new int*[n];
  for (int i = 0; i < n; ++i) {
    copy_array[i] = new int[n];
  }

  // заполнение первого массива
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> array[i][j];
    }
  }
  // заполнение второго массива нулями
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      copy_array[i][j] = 0;
    }
  }
  if (n == 1) {
    std::cout << 0;
  } else {
    for (int k = 0; k < t; ++k) {

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          copy_array[i][j] = array[i][j];
        }
      }

      //для угловых элементов
      if ((copy_array[0][1] + copy_array[1][1] + copy_array[1][0]) == 3) {
        array[0][0] = 1;
      } else if ((copy_array[0][1] + copy_array[1][1] + copy_array[1][0]) == 2) {
        array[0][0] = copy_array[0][0];
      } else {
        array[0][0] = 0;
      }
      if ((copy_array[0][n - 2] + copy_array[1][n - 2] + copy_array[1][n - 1]) == 3) {
        array[0][n - 1] = 1;
      } else if ((copy_array[0][n - 2] + copy_array[1][n - 2] + copy_array[1][n - 1]) == 2) {
        array[0][n - 1] = copy_array[0][n - 1];
      } else {
        array[0][n - 1] = 0;
      }
      if ((copy_array[n - 2][0] + copy_array[n - 2][1] + copy_array[n - 1][1]) == 3) {
        array[n - 1][0] = 1;
      } else if ((copy_array[n - 2][0] + copy_array[n - 2][1] + copy_array[n - 1][1]) == 2) {
        array[n - 1][0] = copy_array[n - 1][0];
      } else {
        array[n - 1][0] = 0;
      }
      if ((copy_array[n - 1][n - 2] + copy_array[n - 2][n - 2] + copy_array[n - 2][n - 1]) == 3) {
        array[n - 1][n - 1] = 1;
      } else if ((copy_array[n - 1][n - 2] + copy_array[n - 2][n - 2] + copy_array[n - 2][n - 1]) == 2) {
        array[n - 1][n - 1] = copy_array[n - 1][n - 1];
      } else {
        array[n - 1][n - 1] = 0;
      }

      if (n >= 3) {
        //для "рамки"
        for (int i = 1; i < n - 1; ++i) {
          if ((copy_array[i - 1][0] + copy_array[i - 1][1] + copy_array[i][1] + copy_array[i + 1][1] +
               copy_array[i + 1][0]) == 2) {
            array[i][0] = copy_array[i][0];
          } else if ((copy_array[i - 1][0] + copy_array[i - 1][1] + copy_array[i][1] + copy_array[i + 1][1] +
                      copy_array[i + 1][0]) == 3) {
            array[i][0] = 1;
          } else {
            array[i][0] = 0;
          }
          if ((copy_array[i - 1][n - 1] + copy_array[i - 1][n - 2] + copy_array[i][n - 2] + copy_array[i + 1][n - 2] +
               copy_array[i + 1][n - 1]) == 2) {
            array[i][n - 1] = copy_array[i][n - 1];
          } else if ((copy_array[i - 1][n - 1] + copy_array[i - 1][n - 2] + copy_array[i][n - 2] +
                      copy_array[i + 1][n - 2] + copy_array[i + 1][n - 1]) == 3) {
            array[i][n - 1] = 1;
          } else {
            array[i][n - 1] = 0;
          }
          if ((copy_array[0][i - 1] + copy_array[1][i - 1] + copy_array[1][i] + copy_array[1][i + 1] +
               copy_array[0][i + 1]) == 2) {
            array[0][i] = copy_array[0][i];
          } else if ((copy_array[0][i - 1] + copy_array[1][i - 1] + copy_array[1][i] + copy_array[1][i + 1] +
                      copy_array[0][i + 1]) == 3) {
            array[0][i] = 1;
          } else {
            array[0][i] = 0;
          }
          if ((copy_array[n - 1][i - 1] + copy_array[n - 2][i - 1] + copy_array[n - 2][i] + copy_array[n - 2][i + 1] +
               copy_array[n - 1][i + 1]) == 2) {
            array[n - 1][i] = copy_array[n - 1][i];
          } else if ((copy_array[n - 1][i - 1] + copy_array[n - 2][i - 1] + copy_array[n - 2][i] +
                      copy_array[n - 2][i + 1] + copy_array[n - 1][i + 1]) == 3) {
            array[n - 1][i] = 1;
          } else {
            array[n - 1][i] = 0;
          }
        }

        //для всех остальных элементов
        for (int i = 1; i < n - 1; ++i) {
          for (int j = 1; j < n - 1; ++j) {
            if ((copy_array[i - 1][j - 1] + copy_array[i - 1][j] + copy_array[i - 1][j + 1] + copy_array[i][j - 1] +
                 copy_array[i][j + 1] + copy_array[i + 1][j - 1] + copy_array[i + 1][j] + copy_array[i + 1][j + 1]) ==
                2) {
              array[i][j] = copy_array[i][j];
            } else if ((copy_array[i - 1][j - 1] + copy_array[i - 1][j] + copy_array[i - 1][j + 1] +
                        copy_array[i][j - 1] + copy_array[i][j + 1] + copy_array[i + 1][j - 1] + copy_array[i + 1][j] +
                        copy_array[i + 1][j + 1]) == 3) {
              array[i][j] = 1;
            } else {
              array[i][j] = 0;
            }
          }
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        copy_array[i][j] = array[i][j];
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n - 1; ++j) {
        std::cout << array[i][j] << " ";
      }
      std::cout << array[i][n - 1] << "\n";
    }
  }

  // очищение
  for (int i = 0; i < n; ++i) {
    delete[] array[i];
  }
  delete[] array;
  for (int i = 0; i < n; ++i) {
    delete[] copy_array[i];
  }
  delete[] copy_array;
}