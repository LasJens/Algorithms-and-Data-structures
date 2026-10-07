#ifndef MERGE_H
#define MERGE_H

template <class T, class P, class U, class V>
void MyMerge(T* array, P left, U middle, V right) {
  T merged_array[1000000];
  int i_left = left;
  int i_right = middle + 1;
  int i_merged_array = 0;

  while (!(middle < i_left) and !(right < i_right)) {
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

template <class T, class P, class R>
void Merge(const T* first_begin, const T* first_end, const P* second_begin, const P* second_end, R* out) {
  for (int i = 0; i < first_end - first_begin; ++i) {
    out[i] = first_begin[i];
  }
  for (int i = 0; i < second_end - second_begin; ++i) {
    out[first_end - first_begin + i] = second_begin[i];
  }
  MyMerge(out, 0, first_end - first_begin - 1, first_end - first_begin + second_end - second_begin - 1);
}

#endif /* MERGE_H */