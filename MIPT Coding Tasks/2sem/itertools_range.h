#ifndef RANGE_H
#define RANGE_H
#define REVERSE_RANGE_IMPLEMENTED

#include <iostream>

class Range {
 private:
  int64_t start_;
  int64_t end_;
  int64_t step_;

 public:
  explicit Range(const int64_t end) : start_(0), end_(end), step_(1){};
  Range(const int64_t start, const int64_t end) : start_(start), end_(end), step_(1){};
  Range(const int64_t start, const int64_t end, const int64_t step) : start_(start), end_(end), step_(step){};

  class Iterator {
   private:
    int64_t current_it_;
    int64_t step_;

   public:
    Iterator(int64_t curr, int64_t step) : current_it_(curr), step_(step){};

    int64_t operator*() {
      return current_it_;
    }

    Iterator& operator++() {
      current_it_ += step_;
      return *this;
    }

    bool operator==(const Iterator& other) {
      if (step_ == 0) {
        return current_it_ == other.current_it_;
      }
      if (step_ > 0) {
        return (current_it_ >= other.current_it_ && current_it_ - other.current_it_ < step_);
      }
      return (current_it_ <= other.current_it_ && current_it_ - other.current_it_ > step_);
    }

    bool operator!=(const Iterator& other) {
      return !(*this == other);
    }
  };

  class ReverseIterator {
   private:
    int64_t current_it_;
    int64_t step_;

   public:
    ReverseIterator(int64_t curr, int64_t step) : current_it_(curr), step_(step){};

    int64_t operator*() {
      return current_it_;
    }

    ReverseIterator& operator++() {
      current_it_ += step_;
      return *this;
    }

    bool operator==(const ReverseIterator& other) {
      if (step_ == 0) {
        return current_it_ == other.current_it_;
      }
      if (step_ > 0) {
        return (current_it_ >= other.current_it_ && current_it_ - other.current_it_ < step_);
      }
      return (current_it_ <= other.current_it_ && current_it_ - other.current_it_ > step_);
    }

    bool operator!=(const ReverseIterator& other) {
      return !(*this == other);
    }
  };

  Iterator begin() const {  // NOLINT
    if (step_ == 0) {
      return {end_, step_};
    }
    if (step_ > 0 && start_ > end_) {
      return {end_, step_};
    }
    if (step_ < 0 && start_ < end_) {
      return {end_, step_};
    }
    return {start_, step_};
  }

  Iterator end() const {  // NOLINT
    return {end_, step_};
  }

  ReverseIterator rbegin() const {  // NOLINT
    if (step_ == 0) {
      return {start_ - step_, -step_};
    }
    if (step_ > 0 && start_ > end_) {
      return {start_ - step_, -step_};
    }
    if (step_ < 0 && start_ < end_) {
      return {start_ - step_, -step_};
    }
    if ((end_ - start_) % step_ == 0) {
      return {end_ - step_, -step_};
    }
    return {start_ + (end_ - start_) / step_ * step_, -step_};
  }

  ReverseIterator rend() const {  // NOLINT
    return {start_ - step_, -step_};
  }
};

#endif
