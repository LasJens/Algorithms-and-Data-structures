#include <iostream>
#include <stdexcept>

#ifndef CPPSTRING_H
#define CPPSTRING_H

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char* string_;
  size_t size_;
  size_t capacity_;
  
 public:
  String();
  String(size_t, char);
  String(const char*); // NOLINT
  String(const char*, size_t);
  String(const String&); // copy constructor
  ~String();
  String& operator=(const String&);
  char& operator[](size_t index);
  const char& operator[](size_t index) const;
  char& At(size_t index);
  const char& At(size_t index) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  char* CStr();
  const char* CStr() const;
  char* Data();
  const char* Data() const;
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  String& PushBack(char);
  String& operator+=(const String&);
  String& Resize(size_t, char);
  void Reserve(size_t);
  void ShrinkToFit();
};

String operator+(const String&, const String&);
bool operator>(const String&, const String&);
bool operator<(const String&, const String&);
bool operator>=(const String&, const String&);
bool operator<=(const String&, const String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
std::ostream& operator<<(std::ostream&, const String&);

#endif /* STRING_H */