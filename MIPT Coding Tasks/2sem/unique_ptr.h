#include <iostream>
#include <memory>
#include <utility>

#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <class T>
class UniquePtr {
 private:
  T* ptr_;
 public:
  UniquePtr();
  explicit UniquePtr(T*);
  UniquePtr(UniquePtr&&) noexcept;
  UniquePtr& operator=(UniquePtr&&) noexcept;
  ~UniquePtr();
  T* Release();
  void Reset(T* ptr = nullptr);
  void Swap(UniquePtr&);
  T* Get() const;
  T& operator*() const; 
  T* operator->() const;
  explicit operator bool() const;
};

template <class T>
UniquePtr<T>::UniquePtr() : ptr_(nullptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(T* ptr) : ptr_(ptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept : ptr_{std::exchange(other.ptr_, nullptr)} {
}
  
template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  delete ptr_;
  ptr_ = std::exchange(other.ptr_, nullptr);
  return *this;
}

template <class T>
UniquePtr<T>::~UniquePtr() {
  delete ptr_;
}

template <class T>
T* UniquePtr<T>::Release() {
  T* raw_ptr = ptr_;
  ptr_ = nullptr;
  return raw_ptr;
}

template <class T>
void UniquePtr<T>::Reset(T* ptr) {
  if (ptr_ != ptr) {
    delete ptr_;
    ptr_ = ptr;
  }
}

template <class T>
void UniquePtr<T>::Swap(UniquePtr<T>& other) {
  T* temp = ptr_;
  ptr_ = other.ptr_;
  other.ptr_ = temp;
}

template <class T>
T* UniquePtr<T>::Get() const {
  return ptr_;
}

template <class T>
T& UniquePtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* UniquePtr<T>::operator->() const {
  return ptr_;
}

template <class T>
UniquePtr<T>::operator bool() const {
  return ptr_ != nullptr;
}

#endif /* UNIQUE_PTR_H */