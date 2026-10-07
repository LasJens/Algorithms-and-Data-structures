#include <iostream>

int Parent(int i) {
  return i / 2;
}
int LeftChild(int i) {
  return 2 * i;
}
int RightChild(int i) {
  return 2 * i + 1;
}

int SiftDown(int* array, int i, int size) {
  int left = LeftChild(i);
  int right = RightChild(i);
  int largest = i;
  if (left <= size && array[left] > array[largest]) {
    largest = left;
  }
  if (right <= size && array[right] > array[largest]) {
    largest = right;
  }
  if (largest != i) {
    std::swap(array[i], array[largest]);
    i = SiftDown(array, largest, size);
  }
  return i;
}

int SiftUp(int* array, int i) {
  int parent = Parent(i);
  if (i > 1 && array[parent] < array[i]) {
    std::swap(array[parent], array[i]);
    i = SiftUp(array, parent);
  }
  return i;
}

void GetMax(int* array, int& size) {
  if (size == 0) {
    std::cout << -1 << '\n';
    return;
  }
  if (size == 1) {
    int max = array[1];
    --size;
    std::cout << "0 " << max << '\n';
    return;
  }
  int max = array[1];
  array[1] = array[size];
  --size;
  std::cout << SiftDown(array, 1, size) << " " << max << '\n';
}

void Add(int* array, int n, int& size, int value) {
  if (size == n) {
    std::cout << -1 << '\n';
    return;
  }
  ++size;
  array[size] = value;
  std::cout << SiftUp(array, size) << '\n';
}

void Delete(int* array, int i, int& size) {
  if (i < 1 || i > size) {
    std::cout << -1 << '\n';
    return;
  }
  int deleted = array[i];
  array[i] = array[size];
  --size;
  SiftUp(array, i);
  SiftDown(array, i, size);
  std::cout << deleted << '\n';
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  auto array = new int[n + 1];
  int size = 0;
  for (int i = 0; i < m; ++i) {
    int asked_action = 0;
    std::cin >> asked_action;
    if (asked_action == 1) {
      GetMax(array, size);
    } else if (asked_action == 2) {
      int wanted_to_add = 0;
      std::cin >> wanted_to_add;
      Add(array, n, size, wanted_to_add);
    } else {
      int ind = 0;
      std::cin >> ind;
      Delete(array, ind, size);
    }
  }
  for (int i = 1; i < size + 1; ++i) {
    std::cout << array[i] << " ";
  }
  delete[] array;
}