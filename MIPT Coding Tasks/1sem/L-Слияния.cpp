#include <iostream>

void Merge(int* array, int left, int middle, int right) {
  auto merged_array = new int[right - left + 1];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;

  //сравниваем элементы между собой и двигаем соответствующий указатель
  while (i_left <= middle and i_right <= right) {
    if (array[i_left] <= array[i_right]) {
      merged_array[i_merged_array] = array[i_left];
      i_merged_array++;
      i_left++;
    } else {
      merged_array[i_merged_array] = array[i_right];
      i_merged_array++;
      i_right++;
    }
  }

  //доставляем в конец элементы большего подмассива
  while (i_left <= middle) {
    merged_array[i_merged_array] = array[i_left];
    i_merged_array++;
    i_left++;
  }
  while (i_right <= right) {
    merged_array[i_merged_array] = array[i_right];
    i_merged_array++;
    i_right++;
  }

  for (int i = left; i <= right; ++i) {
    array[i] = merged_array[i - left];
    // std::cout<< array[i] << " ";
  }
  delete[] merged_array;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int k = 0;
  std::cin >> k;
  auto array = new int*[k];
  auto n_array = new int[k];
  for (int i = 0; i < k; ++i) {
    array[i] = new int[1000000];
  }
  for (int i = 0; i < k; ++i) {
    int n = 0;
    std::cin >> n;
    n_array[i] = n;
    for (int j = 0; j < n; ++j) {
      std::cin >> array[i][j];
    }
  }
  int counter = k;
  while (counter > 1) {
    for (int i = 0; i < counter - counter % 2; i += 2) {
      for (int j = 0; j < n_array[i]; ++j) {
        array[i / 2][j] = array[i][j];
      }
      for (int j = 0; j < n_array[i + 1]; ++j) {
        array[i / 2][j + n_array[i]] = array[i + 1][j];
      }
    }

    for (int i = 0; i < counter / 2; ++i) {
      Merge(array[i], 0, n_array[2 * i] - 1, n_array[2 * i + 1] + n_array[2 * i] - 1);
    }
    for (int i = 0; i < counter / 2; ++i) {
      n_array[i] = n_array[2 * i] + n_array[2 * i + 1];
    }
    if (counter % 2 == 0) {
      counter = counter / 2;
    } else {
      for (int j = 0; j < n_array[counter - 1]; ++j) {
        array[counter / 2][j] = array[counter - 1][j];
      }
      n_array[counter / 2] = n_array[counter - 1];
      counter = counter / 2 + 1;
    }
  }
  for (int j = 0; j < n_array[0] - 1; ++j) {
    std::cout << array[0][j] << " ";
  }
  std::cout << array[0][n_array[0] - 1];
  for (int i = 0; i < k; ++i) {
    delete[] array[i];
  }
  delete[] array;
  delete[] n_array;
}
