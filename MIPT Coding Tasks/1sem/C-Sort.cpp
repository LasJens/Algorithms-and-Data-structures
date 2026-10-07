#ifndef SORT_H
#define SORT_H

template <class T>
void Merge(T* array, int left, int middle, int right) {
  T merged_array[100000];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;

  while (!(middle < i_left) && !(right < i_right)) {
    if (!(array[i_right] < array[i_left])) {
      merged_array[i_merged_array] = array[i_left];
      i_merged_array++;
      i_left++;
    } else {
      merged_array[i_merged_array] = array[i_right];
      i_merged_array++;
      i_right++;
    }
  }

  while (!(middle < i_left)) {
    merged_array[i_merged_array] = array[i_left];
    i_merged_array++;
    i_left++;
  }
  while (!(right < i_right)) {
    merged_array[i_merged_array] = array[i_right];
    i_merged_array++;
    i_right++;
  }

  for (int i = left; !(right < i); ++i) {
    array[i] = merged_array[i - left];
  }
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

template <class T>
void Sort(T* begin, T* end) {
  int n = end - 1 - begin;
  MergeSort(begin, 0, n);
}

#endif /* SORT_H */