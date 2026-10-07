#include <iostream>

void Merge(int* c, int const* a, int const* b, int n_a, int n_b) {
  int i_a = 0;
  int i_b = 0;
  int i_c = 0;
  while (i_a < n_a && i_b < n_b) {
    if (a[i_a] <= b[i_b]) {
      c[i_c] = a[i_a];
      ++i_c;
      ++i_a;
    } else {
      c[i_c] = b[i_b];
      ++i_c;
      ++i_b;
    }
  }
  while (i_a < n_a) {
    c[i_c] = a[i_a];
    ++i_c;
    ++i_a;
  }
  while (i_b < n_b) {
    c[i_c] = b[i_b];
    ++i_c;
    ++i_b;
  }
}

void Mergesort(int n, int* array) {
  if (n == 1 || n == 0) {
    return;
  }
  int mid = n / 2;
  auto left = new int[mid];
  for (int i = 0; i < mid; ++i) {
    left[i] = array[i];
  }
  auto right = new int[n - mid];
  for (int i = 0; i < n - mid; ++i) {
    right[i] = array[mid + i];
  }
  Mergesort(mid, left);
  Mergesort(n - mid, right);
  auto c = new int[n]();
  Merge(c, left, right, mid, n - mid);
  for (int i = 0; i < n; ++i) {
    array[i] = c[i];
  }
  delete[] left;
  delete[] right;
  delete[] c;
}

bool Check(int scope, int m, int k, int* array, int n) {
  int num = 0;
  int i = 0;
  while (i < n - k + 1) {
    if (array[i + k - 1] - array[i] <= scope) {
      ++num;
      i += k;
    } else {
      ++i;
    }
  }
  return (num >= m);
}

int main() {
  int n;
  int m;
  int k;
  std::cin >> n >> m >> k;
  auto array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  Mergesort(n, array);
  int left = 0;
  int right = array[n - 1] - array[0];
  int mid;
  while (right - left > 1) {
    mid = (left + right) / 2;
    //std::cout << Check(mid, m, k, array, n);
    if (Check(mid, m, k, array, n)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  if (Check(left, m, k, array, n)) {
    std::cout << left;
  } else {
    std::cout << right;
  }
  delete[] array;
  return 0;
}