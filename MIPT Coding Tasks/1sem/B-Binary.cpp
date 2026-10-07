#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value);
template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value);
template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value);

template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
  return (LowerBound(begin, end, value) != UpperBound(begin, end, value));
}

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
  int left = 0;
  int right = end - begin;
  int middle = (right + left) / 2;
  while (1 < right - left) {
    if (begin[middle] < value) {
      left = middle;
    } else {
      right = middle;
    }
    middle = (left + right) / 2;
  }
  if ((begin[left] < value) != 0) {
    return begin + right;
  }
  return begin + left;
}

template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
  int left = 0;
  int right = end - begin;
  int middle = (right + left) / 2;
  while (1 < right - left) {
    if (value < begin[middle]) {
      right = middle;
    } else {
      left = middle;
    }
    middle = (left + right) / 2;
  }
  if (value < begin[left]) {
    return begin + left;
  }
  return begin + right;
}

#endif /* BINARY_SEARCH_H */