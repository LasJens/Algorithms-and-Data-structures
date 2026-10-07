#ifndef ANY_H
#define ANY_H

#include <utility>
#include <memory>
#include <stdexcept>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "Error";
  }
};

class IHolder {
 public:
  virtual ~IHolder() = default;
  virtual IHolder* Clone() const = 0;
};

template <class T>
class AnyHolder : public IHolder {
 private:
  T value_;

 public:
  AnyHolder(T value) : value_(value) {  // NOLINT
  }

  IHolder* Clone() const override {
    return new AnyHolder<T>(value_);
  }

  T Get() const {
    return value_;
  }
};

class Any {
 private:
  std::shared_ptr<IHolder> ptr_ = nullptr;

 public:
  Any() = default;

  Any(const Any& other) : ptr_(other.ptr_->Clone()) {
  }

  Any(Any&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {
  }

  template <class T>
  Any(const T value) : ptr_(new AnyHolder<T>(value)) {  // NOLINT
  }

  ~Any() = default;

  Any& operator=(const Any&) = default;

  Any& operator=(Any&& other) noexcept {
    if (this == &other) {
      return *this;
    }
    ptr_ = std::exchange(other.ptr_, nullptr);
    return *this;
  }

  template <class T>
  Any& operator=(const T& value) {
    Any tmp(value);
    ptr_ = tmp.ptr_;
    return *this;
  }
  
  void Swap(Any& other) {
    Any temp;
    temp.ptr_ = ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = temp.ptr_;
  }

  void Reset() {
    ptr_ = nullptr;
  }

  bool HasValue() {
    return ptr_ != nullptr;
  }

  template <class T>
  friend T AnyCast(const Any& value);
};

template <class T>
T AnyCast(const Any& value) {
  if (auto holder = dynamic_cast<AnyHolder<T>*>(value.ptr_.get())) {
    return holder->Get();
  }
  throw BadAnyCast{};
}

#endif
