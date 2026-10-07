#include <iostream>
#include <memory>
#include <utility>
#include <stdexcept>

#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#define WEAK_PTR_IMPLEMENTED

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

template <class T>
class SharedPtr;

template <class T>
class WeakPtr;

struct Cnt {
  size_t s_cnt = 0;
  size_t w_cnt = 0;
};

template <class T>
class SharedPtr {
 private:
  T* ptr_ = nullptr;
  Cnt* cnt_ = nullptr;
 public:
  SharedPtr();
  SharedPtr(T*); // NOLINT
  SharedPtr(const WeakPtr<T>&); // NOLINT
  SharedPtr(const SharedPtr&);
  SharedPtr& operator=(const SharedPtr&);
  SharedPtr(SharedPtr&&) noexcept;
  SharedPtr& operator=(SharedPtr&&) noexcept;
  ~SharedPtr();
  void Reset(T* ptr = nullptr);
  void Swap(SharedPtr&);
  T* Get() const;
  size_t UseCount() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
  friend class WeakPtr<T>;
};

template <class T>
class WeakPtr {
 private:
  T* ptr_ = nullptr;
  Cnt* cnt_ = nullptr;
 public:
  WeakPtr();
  WeakPtr(const SharedPtr<T>&); // NOLINT
  WeakPtr(const WeakPtr<T>&);
  WeakPtr<T>& operator=(const WeakPtr<T>&);
  WeakPtr(WeakPtr<T>&&) noexcept;
  WeakPtr<T>& operator=(WeakPtr<T>&&) noexcept;
  ~WeakPtr();
  void Swap(WeakPtr<T>&);
  void Reset();
  size_t UseCount() const;
  bool Expired() const;
  SharedPtr<T> Lock() const;
  friend class SharedPtr<T>;
};

template <class T>
SharedPtr<T>::SharedPtr() : ptr_(nullptr), cnt_(nullptr) {
}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr) : ptr_(ptr), cnt_(nullptr) {
  if (ptr_) {
    cnt_ = new Cnt;
    cnt_->s_cnt = 1;
    cnt_->w_cnt = 0;
  }
}

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& weak_ptr) : ptr_(weak_ptr.ptr_), cnt_(weak_ptr.cnt_) {
  if (weak_ptr.Expired()) {
    throw BadWeakPtr{};
  }
  ++cnt_->s_cnt;
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : ptr_(other.ptr_), cnt_(other.cnt_) {
  if (cnt_) {
    ++(cnt_->s_cnt);
  }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
  if (this == &other) {
    return *this;
  }
  if (cnt_) {
    if (cnt_->s_cnt == 1) {
      delete ptr_;
      if (cnt_->w_cnt == 0) {
        delete cnt_;
      } else {
        --(cnt_->s_cnt);
      }
    } else {
      --(cnt_->s_cnt);
    }
  }
  ptr_ = other.ptr_;
  cnt_ = other.cnt_;
  if (cnt_) {
    ++(cnt_->s_cnt);
  }
  return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept : ptr_{std::exchange(other.ptr_, nullptr)}, cnt_{std::exchange(other.cnt_, nullptr)} {
}
  
template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  if (cnt_) {
    if (cnt_->s_cnt == 1) {
      delete ptr_;
      if (cnt_->w_cnt == 0) {
        delete cnt_;
      } else {
        --(cnt_->s_cnt);
      }
    } else {
      --(cnt_->s_cnt);
    }
  }
  ptr_ = std::exchange(other.ptr_, nullptr);
  cnt_ = std::exchange(other.cnt_, nullptr);
  return *this;
}

template <class T>
SharedPtr<T>::~SharedPtr() {
  if (cnt_) {
    if (cnt_->s_cnt == 1) {
      delete ptr_;
      if (cnt_->w_cnt == 0) {
        delete cnt_;
      } else {
        --(cnt_->s_cnt);
      }
    } else {
      --(cnt_->s_cnt);
    }
  }
}

template <class T>
void SharedPtr<T>::Reset(T* ptr) {
  if (cnt_) {
    if (cnt_->s_cnt == 1) {
      delete ptr_;
      ptr_ = nullptr;
      if (cnt_->w_cnt == 0) {
        delete cnt_;
        cnt_ = nullptr;
      } else {
        --(cnt_->s_cnt);
      }
    } else {
      --(cnt_->s_cnt);
    }
  }
  ptr_ = ptr;
  if (ptr_) {
    cnt_ = new Cnt;
    cnt_->s_cnt = 1;
    cnt_->w_cnt = 0;
  } else {
    cnt_ = nullptr;
  }
}

template <class T>
void SharedPtr<T>::Swap(SharedPtr<T>& other) {
  T* temp = ptr_;
  Cnt* tempi = cnt_;
  ptr_ = other.ptr_;
  cnt_ = other.cnt_;
  other.ptr_ = temp;
  other.cnt_ = tempi;
}

template <class T>
T* SharedPtr<T>::Get() const {
  return ptr_;
}

template <class T>
size_t SharedPtr<T>::UseCount() const {
  if (cnt_) {
    return cnt_->s_cnt;
  }
  return 0;
}

template <class T>
T& SharedPtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* SharedPtr<T>::operator->() const {
  return ptr_;
}

template <class T>
SharedPtr<T>::operator bool() const {
  return ptr_ != nullptr;
}


template <class T>
WeakPtr<T>::WeakPtr() : ptr_(nullptr), cnt_(nullptr) {
}

template <class T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& s_ptr) : ptr_(s_ptr.ptr_), cnt_(s_ptr.cnt_) {
  if (cnt_) {
    ++cnt_->w_cnt;
  }
}

template <class T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& other) : ptr_(other.ptr_), cnt_(other.cnt_) {
  if (cnt_) {
    ++cnt_->w_cnt;
  }
}

template <class T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& other) {
  if (this == &other) {
    return *this;
  }
  if (cnt_) {
    if (cnt_->s_cnt == 0 && cnt_->w_cnt == 1) {
      delete cnt_;
    } else {
      --cnt_->w_cnt;
    }
  }
  ptr_ = other.ptr_;
  cnt_ = other.cnt_;
  ++cnt_->w_cnt;
  return *this;
}

template <class T>
WeakPtr<T>::WeakPtr(WeakPtr<T>&& other) noexcept
    : ptr_(std::exchange(other.ptr_, nullptr)), cnt_(std::exchange(other.cnt_, nullptr)) {
}

template <class T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  if (cnt_) {
    if (cnt_->s_cnt == 0 && cnt_->w_cnt == 1) {
      delete cnt_;
    } else {
      --cnt_->w_cnt;
    }
  }
  ptr_ = std::exchange(other.ptr_, nullptr);
  cnt_ = std::exchange(other.cnt_, nullptr);
  return *this;
}

template <class T>
WeakPtr<T>::~WeakPtr() {
  if (cnt_) {
    if (cnt_->s_cnt == 0 && cnt_->w_cnt == 1) {
      delete cnt_;
    } else {
      --cnt_->w_cnt;
    }
  }
}

template <class T>
void WeakPtr<T>::Swap(WeakPtr<T>& other) {
  T* temp = ptr_;
  Cnt* tempi = cnt_;
  ptr_ = other.ptr_;
  cnt_ = other.cnt_;
  other.ptr_ = temp;
  other.cnt_ = tempi;
}

template <class T>
void WeakPtr<T>::Reset() {
  if (cnt_) {
    if (cnt_->s_cnt == 0 && cnt_->w_cnt == 1) {
      delete cnt_;
      cnt_ = nullptr;
    } else {
      --cnt_->w_cnt;
    }
  }
  ptr_ = nullptr;
  cnt_ = nullptr;
}

template <class T>
size_t WeakPtr<T>::UseCount() const {
  if (cnt_) {
    return cnt_->s_cnt;
  }
  return 0;
}

template <class T>
bool WeakPtr<T>::Expired() const {
  if (cnt_ == nullptr) {
    return true;
  }
  return cnt_->s_cnt == 0;
}

template <class T>
SharedPtr<T> WeakPtr<T>::Lock() const {
  if (Expired()) {
    return SharedPtr<T>();
  }
  return SharedPtr<T>(*this);
}

#endif /* SHARED_PTR_H */