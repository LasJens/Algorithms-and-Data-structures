#include <iostream>

//функция, которая ищет горизонтильную линию из единиц
int HorizontalLineFinder(char**& array, int n, int m) {
  int flag = 0;
  int counter = 0;
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      if ((array[i][j] == '1') && (array[i][j + 1] == '1')) {
        flag = 1;
        break;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    if ((flag == 1) && (array[i][0] == '1')) {
      counter++;
    }
  }
  return flag + counter;
}

//функция, которая ищет вертикальную линию из единиц
int VerticalLineFinder(char**& array, int n, int m) {
  int flag = 0;
  int counter = 0;
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      if ((array[i][j] == '1') && (array[i + 1][j] == '1')) {
        flag = 1;
        break;
      }
    }
  }
  for (int j = 0; j < m; ++j) {
    if ((flag == 1) && (array[0][j] == '1')) {
      counter++;
    }
  }
  return flag + counter;
}

//функция, которая ищет дистанцию между горизонтальными рядами из единиц
int DistanceHorizontal(char**& array, int n) {
  int r1 = 0, r2 = 0;
  for (int i = 0; i < n; ++i) {
    if (array[i][0] == '1') {
      r1 = i;
      break;
    }
  }
  for (int i = 0; i < n; ++i) {
    if ((array[i][0] == '1') && i != r1) {
      r2 = i;
      break;
    }
  }
  return r2 - r1 - 1;
}

//функция, которая ищет дистанцию между вертикальными рядами из единиц
int DistanceVertical(char**& array, int m) {
  int r1 = 0, r2 = 0;
  for (int j = 0; j < m; ++j) {
    if (array[0][j] == '1') {
      r1 = j;
      break;
    }
  }
  for (int j = 0; j < m; ++j) {
    if ((array[0][j] == '1') && j != r1) {
      r2 = j;
      break;
    }
  }
  return r2 - r1 - 1;
}

int main() {

  int n, m;
  std::cin >> n >> m;

  // выделение памяти
  auto array = new char*[n];
  for (int i = 0; i < n; ++i) {
    array[i] = new char[m];
  }

  // заполнение
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> array[i][j];
    }
  }

  if ((HorizontalLineFinder(array, n, m) >= 2) && (VerticalLineFinder(array, n, m) >= 2)) {
    std::cout << "Square";  //проверка на клетку
  } else if (((HorizontalLineFinder(array, n, m) == 2) && (VerticalLineFinder(array, n, m) == 0)) ||
             ((HorizontalLineFinder(array, n, m) == 0) && (VerticalLineFinder(array, n, m) == 2)) ||
             ((HorizontalLineFinder(array, n, m) == 0) && (VerticalLineFinder(array, n, m) == 0))) {
    std::cout << "?";  //проверка на на одиночную строку/столбец или на таблцу из нулей
  } else if (((HorizontalLineFinder(array, n, m) > 2) && (DistanceHorizontal(array, n) >= m)) ||
             ((VerticalLineFinder(array, n, m) > 2) && (DistanceVertical(array, m) >= n))) {
    std::cout << "?";  // проверка на расстояние между рядами больше длины/ширины таблицы
  } else if (HorizontalLineFinder(array, n, m) > 2) {
    std::cout << "Line";  //линия
  } else if (VerticalLineFinder(array, n, m) > 2) {
    std::cout << "Vertical line";  //вертикальная линия
  }

  // очищение
  for (int i = 0; i < n; ++i) {
    delete[] array[i];
  }
  delete[] array;
}