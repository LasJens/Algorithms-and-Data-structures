#include <iostream>

int64_t Merge(int64_t* array, int left, int middle, int right) {
  int64_t merged_array[500000];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;
  int64_t inversions_counter = 0;

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
      inversions_counter = inversions_counter + middle - i_left + 1;
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
  return inversions_counter;
}

int64_t MergeSort(int64_t* array, int left, int right, int64_t* ptr_counter) {
  if (left >= right) {
  } else {
    int middle = (left + right) / 2;
    MergeSort(array, left, middle, ptr_counter);
    MergeSort(array, middle + 1, right, ptr_counter);
    *ptr_counter += Merge(array, left, middle, right);
  }
  return *ptr_counter;
}

int main() {
  int n_a = 0;
  std::cin >> n_a;
  int64_t a[500000];
  for (int i = 0; i < n_a; ++i) {
    std::cin >> a[i];
  }
  int64_t counter = 0;
  int64_t* ptr_counter = &counter;
  std::cout << MergeSort(a, 0, n_a - 1, ptr_counter);
}