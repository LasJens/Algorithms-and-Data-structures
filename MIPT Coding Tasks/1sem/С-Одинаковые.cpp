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
  int n_a = 0, n_b = 0;
  std::cin >> n_a;
  int a[100000];
  for (int i = 0; i < n_a; ++i) {
    std::cin >> a[i];
  }
  std::cin >> n_b;
  int b[100000];
  for (int i = 0; i < n_b; ++i) {
    std::cin >> b[i];
  }

  MergeSort(a, 0, n_a - 1);
  MergeSort(b, 0, n_b - 1);

  int i_a = 0, i_b = 0;
  while (true) {
    if (a[0] != b[0]) {
      std::cout << "NO";
      break;
    }
    if ((i_a == n_a - 1) and (i_b == n_b - 1) and (a[n_a - 1] == b[n_b - 1])) {
      std::cout << "YES";
      break;
    }
    if ((i_a >= n_a) or (i_b >= n_b) or ((i_a == n_a - 1) and (i_b == n_b - 1) and (a[n_a - 1] != b[n_b - 1]))) {
      std::cout << "NO";
      break;
    }
    if ((a[i_a] == b[i_b]) and (i_a < n_a - 1) and (i_b < n_b - 1)) {
      i_a++;
      i_b++;
    } else if ((a[i_a] == b[i_b]) and (i_a == n_a - 1)) {
      i_b++;
    } else if ((a[i_a] == b[i_b]) and (i_b == n_b - 1)) {
      i_a++;
    } else if (a[i_a] == a[i_a - 1]) {
      i_a++;
    } else if (b[i_b] == b[i_b - 1]) {
      i_b++;
    } else {
      std::cout << "NO";
      break;
    }
  }
}