#include <iostream>
#include "cppstring.h"
#include "cmath"

String::String() : string_(nullptr), size_(0), capacity_(0) {
}

String::String(size_t size, char symbol) : string_(nullptr), size_(size), capacity_(size) {
  if (size != 0) {
    string_ = new char[size_ + 1];
    string_[size] = '\0';
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = symbol;
    }
  }
}

String::String(const char* array) : string_(nullptr), size_(0), capacity_(0) {
  size_t i = 0;
  while (array[i] != '\0') {
    ++i;
  }
  if (i != 0) {
    size_ = i;
    capacity_ = i;
    string_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = array[i];
    }
    string_[size_] = '\0';
  }
}

String::String(const char* array, size_t size) : string_(nullptr), size_(size), capacity_(size) {
  if (size != 0) {
    string_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = array[i];
    }
    string_[size_] = '\0';
  }
}

String::String(const String& str) : string_(nullptr), size_(str.size_), capacity_(str.capacity_) {
  if (size_ != 0) {
    string_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = str.string_[i];
    }
    string_[size_] = '\0';
  }
}

String::~String() {
  delete[] string_;
}

String& String::operator=(const String& str) {
  if (this == &str) {
    return *this;
  }
  delete[] string_;
  string_ = nullptr;
  size_ = str.size_;
  capacity_ = str.capacity_;
  if (size_ > 0) {
    string_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      string_[i] = str.string_[i];
    }
    string_[size_] = '\0';
  }
  return *this;
}

char& String::operator[](size_t index) {
  return *(string_ + index);
}

const char& String::operator[](size_t index) const{
  return *(string_ + index);
}

char& String::At(size_t index) {
  if (index >= size_) {
    throw StringOutOfRange{};
  }
  return *(string_ + index);
}

const char& String::At(size_t index) const {
  if (index >= size_) {
    throw StringOutOfRange{};
  }
  return *(string_ + index);
}

char& String::Front() {
  return *string_;
}

const char& String::Front() const {
  return *string_;
}

char& String::Back() {
  return *(string_ + size_ - 1);
}

const char& String::Back() const {
  return *(string_ + size_ - 1);
}

char* String::CStr() {
  return string_;
}

const char* String::CStr() const {
  return string_;
}
  
char* String::Data() {
  return string_;
}
  
const char* String::Data() const {
  return string_;
}

bool String::Empty() const {
  return size_ == 0;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_= 0;
  if (string_ == nullptr) {
    return;
  }
  string_[0] = '\0';
}

void String::Swap(String& other) {
  auto reserve = string_;
  string_ = other.string_;
  other.string_ = reserve;
  auto res_size = size_;
  size_ = other.size_;
  other.size_ = res_size;
  auto res_cap = capacity_;
  capacity_ = other.capacity_;
  other.capacity_ = res_cap;
}

void String::PopBack() {
  if (size_ == 0) {
    return;
  }
  string_[size_ - 1] = '\0';
  --size_;
}

String& String::PushBack(char symbol) {
  if (capacity_ > size_) {
    string_[size_] = symbol;
    string_[size_ + 1] = '\0';
    ++size_;
  } else {
    capacity_ = 2 * capacity_ + 2;
    String array(capacity_, '\0');
    array.capacity_ = capacity_;
    array.size_ = size_ + 1;
    for (size_t i = 0; i < size_; ++i) {
      array[i] = string_[i];
    }
    array[size_] = symbol;
    array[size_ + 1] = '\0';
    Swap(array);
  }
  return *this;
}

String& String::operator+=(const String& str) {
  if (str.size_ == 0) {
    return *this;
  }
  size_t i = 0;
  while (str[i] != '\0') {
    PushBack(str[i]);
    ++i;
  }
  return *this;
}

String& String::Resize(size_t new_size, char symbol) {
  if (new_size <= capacity_) {
    if (new_size > size_) {
      for (size_t i = size_; i < new_size; ++i) {
        string_[i] = symbol;
      }
    }
    size_ = new_size;
    string_[new_size] = '\0';
  } else {
    String array(new_size, '\0');
    for (size_t i = 0; i < size_; ++i) {
      array[i] = string_[i];
    }
    for (size_t i = size_; i < new_size; ++i) {
      array[i] = symbol;
    }
    array[new_size] = '\0';
    Swap(array);
  }
  return *this;
}

void String::Reserve(size_t new_capacity) {
  if (capacity_ < new_capacity) {
    capacity_ = new_capacity;
    String array(capacity_, '\0');
    array.capacity_ = capacity_;
    array.size_ = size_;
    for (size_t i = 0; i < size_; ++i) {
      array[i] = string_[i];
    }
    array[size_] = '\0';
    Swap(array);
  }
}

void String::ShrinkToFit() {
  capacity_ = size_;
}

String operator+(const String& s1, const String& s2) {
  String res = s1;
  res += s2;
  return res;
}

bool operator>(const String& s1, const String& s2) {
  size_t i_first = 0;
  size_t i_second = 0;
  while (i_first < s1.Size() && i_second < s2.Size()) {
    if (s1[i_first] != s2[i_second]) {
      return s1[i_first] > s2[i_second];
    }
    ++i_first;
    ++i_second;
  }
  if (i_first == s1.Size() && i_second != s2.Size()) {
    return false;
  }
  if (i_first != s1.Size() && i_second == s2.Size()) {
    return true;
  }
  return false;
}

bool operator<(const String& s1, const String& s2) {
  size_t i_first = 0;
  size_t i_second = 0;
  while (i_first < s1.Size() && i_second < s2.Size()) {
    if (s1[i_first] != s2[i_second]) {
      return s1[i_first] < s2[i_second];
    }
    ++i_first;
    ++i_second;
  }
  if (i_first == s1.Size() && i_second != s2.Size()) {
    return true;
  }
  if (i_first != s1.Size() && i_second == s2.Size()) {
    return false;
  }
  return false;
}

bool operator>=(const String& s1, const String& s2) {
  return !(s1 < s2);
}

bool operator<=(const String& s1, const String& s2) {
  return !(s1 > s2);
}

bool operator==(const String& s1, const String& s2) {
  return !((s1 > s2) || (s1 < s2));
}

bool operator!=(const String& s1, const String& s2) {
  return !(s1 == s2);
}

std::ostream& operator<<(std::ostream& sout, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    sout << str[i];
  }
  return sout;
}