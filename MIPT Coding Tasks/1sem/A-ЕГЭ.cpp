#include <iostream>

struct EGE {
  char name[40];
  char surname[40];
  int inf;
  int maths;
  int rus;
};

bool operator>(EGE& p_1, EGE& p_2) {
  return p_1.inf + p_1.maths + p_1.rus > p_2.inf + p_2.maths + p_2.rus;
}

template <class T>
void Merge(T* array, int left, int middle, int right) {
  auto merged_array = new T[right - left + 1];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;

  while (!(middle < i_left) && !(right < i_right)) {
    if (array[i_right] > array[i_left]) {
      for (int i = 0; i < 50; ++i) {
        merged_array[i_merged_array].name[i] = array[i_left].name[i];
        merged_array[i_merged_array].surname[i] = array[i_left].surname[i];
      }
      merged_array[i_merged_array].inf = array[i_left].inf;
      merged_array[i_merged_array].maths = array[i_left].maths;
      merged_array[i_merged_array].rus = array[i_left].rus;
      i_merged_array++;
      i_left++;
    } else {
      for (int i = 0; i < 50; ++i) {
        merged_array[i_merged_array].name[i] = array[i_right].name[i];
        merged_array[i_merged_array].surname[i] = array[i_right].surname[i];
      }
      merged_array[i_merged_array].inf = array[i_right].inf;
      merged_array[i_merged_array].maths = array[i_right].maths;
      merged_array[i_merged_array].rus = array[i_right].rus;
      i_merged_array++;
      i_right++;
    }
  }

  while (!(middle < i_left)) {
    for (int i = 0; i < 50; ++i) {
      merged_array[i_merged_array].name[i] = array[i_left].name[i];
      merged_array[i_merged_array].surname[i] = array[i_left].surname[i];
    }
    merged_array[i_merged_array].inf = array[i_left].inf;
    merged_array[i_merged_array].maths = array[i_left].maths;
    merged_array[i_merged_array].rus = array[i_left].rus;
    i_merged_array++;
    i_left++;
  }
  while (!(right < i_right)) {
    for (int i = 0; i < 50; ++i) {
      merged_array[i_merged_array].name[i] = array[i_right].name[i];
      merged_array[i_merged_array].surname[i] = array[i_right].surname[i];
    }
    merged_array[i_merged_array].inf = array[i_right].inf;
    merged_array[i_merged_array].maths = array[i_right].maths;
    merged_array[i_merged_array].rus = array[i_right].rus;
    i_merged_array++;
    i_right++;
  }

  for (int i = left; !(right < i); ++i) {
    for (int j = 0; j < 50; ++j) {
      array[i].name[j] = merged_array[i - left].name[j];
      array[i].surname[j] = merged_array[i - left].surname[j];
    }
    array[i].inf = merged_array[i - left].inf;
    array[i].maths = merged_array[i - left].maths;
    array[i].rus = merged_array[i - left].rus;
  }
  delete[] merged_array;
}

template <class T>
void MergeSort(T* array, int left, int right) {
  if (!(left < right)) {
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
  auto array = new EGE[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i].name;
    std::cin >> array[i].surname;
    std::cin >> array[i].inf;
    std::cin >> array[i].maths;
    std::cin >> array[i].rus;
  }
  MergeSort(array, 0, n - 1);
  for (int i = n - 1; i > 0; --i) {
    std::cout << array[i].name << " " << array[i].surname << "\n";
  }
  std::cout << array[0].name << " " << array[0].surname;
  delete[] array;
}
