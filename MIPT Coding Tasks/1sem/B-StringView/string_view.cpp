#include "string_view.h"
#include <iostream>
#include <cstring>

StringView::StringView() : str_(nullptr) {
}

StringView::StringView(const char* string) : str_(string), size_(strlen(str_)) {
}

StringView::StringView(const char* string, size_t size) : str_(string), size_(size) {
}

const char& StringView::operator[](size_t i) const {
  return *(str_ + i);
}

const char& StringView::Front() const {
  return *str_;
}

const char& StringView::Back() const {
  return *(str_ + size_ - 1);
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return size_ == 0;
}

const char* StringView::Data() const {
  return str_;
}

void StringView::Swap(StringView& other) {
  auto reserve = str_;
  str_ = other.str_;
  other.str_ = reserve;
  auto res_size = size_;
  size_ = other.size_;
  other.size_ = res_size;
}

void StringView::RemovePrefix(size_t prefix_size) {
  str_ = str_ + prefix_size;
  size_ = size_ - prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ = size_ - suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count = -1) {
  size_t current = Size();
  size_t len = current - pos > count ? count : current - pos;
  auto str = str_ + pos;
  StringView ans_str(str, len);
  return ans_str;
}