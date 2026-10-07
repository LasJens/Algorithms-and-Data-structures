#include <iostream>

void Merge(int* array, int left, int middle, int right) {
  int merged_array[100000];
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
  }
}

void MergeSort(int* array, int left, int right) {
  if (left >= right) {
  } else {
    int middle = (left + right) / 2;
    MergeSort(array, left, middle);
    MergeSort(array, middle + 1, right);
    Merge(array, left, middle, right);
  }
}

int main() {
  int n, m, k;
  std::cin >> n >> m >> k;
  int array[100000];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  MergeSort(array, 0, n - 1);
  int left = 0, right = array[n - 1] - array[0];
  int group_array[100000];
  if (k == 1) {
    std::cout << 0;
  } else {
    for (int i = 0; i < n - k + 1; ++i) {
      group_array[i] = array[i + k - 1] - array[i];
    }
    int value = (right + left) / 2;
    int m_counter = 0;
    while (left < right - 1) {
      for (int i = 0; i < n - k + 1; ++i) {
        if (group_array[i] <= value) {
          m_counter++;
          i += k - 1;
        }
      }
      if (m_counter >= m) {
        right = value;
      } else {
        left = value;
      }
      value = (right + left) / 2;
      m_counter = 0;
    }
    if (m_counter >= m) {
      std::cout << value;
    } else {
      std::cout << value + 1;
    }
  }
}