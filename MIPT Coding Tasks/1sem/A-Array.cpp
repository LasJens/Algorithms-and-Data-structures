#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

template <class T, size_t N>
class Array {
 public:
  T array[N];

  const T& operator[](size_t i) const {
    return *(array + i);
  }

  T& operator[](size_t i) {
    return *(array + i);
  }

  const T& Front() const {
    return *array;
  }

  T& Front() {
    return *array;
  }

  const T& Back() const {
    return *(array + N - 1);
  }

  T& Back() {
    return *(array + N - 1);
  }

  const T* Data() const {
    return array;
  }

  T* Data() {
    return array;
  }
  
  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return Size() == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      *(array + i) = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      T reserve = *(array + i);
      *(array + i) = other[i];
      other[i] = reserve;
    }
  }
};

#endif /* ARRAY_H */