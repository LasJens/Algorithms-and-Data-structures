#ifndef SORT_TEMPLATES_H_
#define SORT_TEMPLATES_H_

#include <iostream>
#include <deque>

template <class T, typename Container = std::deque<T> >
class Stack {
 private:
  Container container_;
 public:
  Stack() = default;
  explicit Stack(const Container& cont) : container_(cont) {
  }
  template <typename Iterator>
  Stack(Iterator begin, Iterator end) : container_(begin, end) {
  }
  const T& Top() const{
    return container_.back();
  }
  T& Top() {
    return container_.back();
  }
  bool Empty() {
    return container_.empty();
  }
  bool Empty() const {
    return container_.empty();
  }
  size_t Size() const {
    return container_.size();
  }
  size_t Size() {
    return container_.size();
  }
  void Push(const T& value) {
    container_.push_back(value);
  }
  void Push(T&& value) {
    container_.push_back(std::move(value));
  }
  template <typename... Args>
  void Emplace(Args&&... args) {
    container_.emplace_back(std::forward<Args>(args)...);
  }
  void Pop() {
    container_.pop_back();
  }
  void Swap(Stack& other) {
    container_.swap(other.container_);
  }
};

#endif