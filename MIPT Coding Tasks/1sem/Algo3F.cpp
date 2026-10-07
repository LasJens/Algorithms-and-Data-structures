#include <iostream>

void Merge(int* array, int left, int middle, int right) {
  int merged_array[100000];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;
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
  int array[101];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  MergeSort(array, 0, n - 1);
  size_t dp[101];
  if (n == 2) {
    std::cout << array[1] - array[0];
  } else {
    dp[0] = 100000;
    dp[1] = array[1] - array[0];
    dp[2] = array[2] - array[0];
    for (int i = 3; i < n; ++i) {
      if (dp[i - 2] + array[i] - array[i - 1] <= dp[i - 3] + array[i] - array[i - 2]) {
        dp[i] = dp[i - 2] + array[i] - array[i - 1];
      } else {
        dp[i] = dp[i - 3] + array[i] - array[i - 2];
      }
    }
    std::cout << dp[n - 1];
  }
}