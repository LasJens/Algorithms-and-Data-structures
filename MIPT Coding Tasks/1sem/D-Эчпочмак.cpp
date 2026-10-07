#include <iostream>

void Merge(int* array, int left, int middle, int right) {
  int merged_array[300000];
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
  int n = 0;
  std::cin >> n;
  int array[300000];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  MergeSort(array, 0, n - 1);

  int ptr_1 = 0;
  int ptr_2 = 1;
  int i = 2;
  int counter_1 = array[0] + array[1];
  int counter_2 = 0;
  int size_1 = 2;
  int size_2 = 0;
  if (n == 1) {
    std::cout << 1 << " " << array[0];
  } else if (n == 2) {
    std::cout << 2 << " " << array[0] + array[1];
  } else {
    while (i <= n - 1) {
      while ((i <= n - 1) and (array[i] <= (array[ptr_1] + array[ptr_2]))) {
        counter_1 += array[i];
        size_1++;
        i++;
      }
      ptr_1++;
      ptr_2++;
      if (counter_1 > counter_2) {
        counter_2 = counter_1;
        size_2 = size_1;
      }
      counter_1 -= array[ptr_1 - 1];
      size_1--;
    }
    if (array[n - 1] + array[n - 2] > counter_2) {
      std::cout << 2 << " " << array[n - 1] + array[n - 2];
    } else {
      std::cout << size_2 << " " << counter_2;
    }
  }
}