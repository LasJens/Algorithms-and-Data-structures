#include <iostream>
#include "cstring.h"

size_t Strlen(const char* str) {
  size_t counter = 0;
  size_t i = 0;
  while (str[i] != '\0') {
    ++counter;
    ++i;
  }
  return counter;
}

int Strcmp(const char* first, const char* second) {
  size_t i_first = 0;
  size_t i_second = 0;
  while (first[i_first] != '\0' && second[i_second] != '\0') {
    if (first[i_first] > second[i_second]) {
      return 1;
    }
    if (first[i_first] < second[i_second]) {
      return -1;
    }
    ++i_first;
    ++i_second;
  }
  if (first[i_first] == '\0' && second[i_second] != '\0') {
    return -1;
  }
  if (first[i_first] != '\0' && second[i_second] == '\0') {
    return 1;
  }
  return 0;
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t i_first = 0;
  size_t i_second = 0;
  while (first[i_first] != '\0' && i_first < count && second[i_second] != '\0' && i_second < count) {
    if (first[i_first] > second[i_second]) {
      return 1;
    }
    if (first[i_first] < second[i_second]) {
      return -1;
    }
    return 0;
    ++i_first;
    ++i_second;
  }
  if (i_first == count && i_second == count) {
    return 0;
  }
  if (i_first == '\0' && i_second != '\0') {
    return -1;
  }
  if (i_first != '\0' && i_second == '\0') {
    return 1;
  }
  return 0;
}

char* Strcpy(char* dest, const char* src) {
  size_t i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    ++i;
  }
  dest[i] = '\0';
  return dest;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  size_t i = 0;
  while (src[i] != '\0' && i < count) {
    dest[i] = src[i];
    ++i;
  }
  while (i < count) {
    dest[i] = '\0';
    ++i;
  }
  return dest;
}

char* Strcat(char* dest, const char* src) {
  size_t i_dest = Strlen(dest);
  size_t i_src = 0;
  while (src[i_src] != '\0') {
    dest[i_dest] = src[i_src];
    ++i_dest;
    ++i_src;
  }
  dest[i_dest] = '\0';
  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  size_t i_dest = Strlen(dest);
  size_t i_src = 0;
  while (src[i_src] != '\0' && i_src < count) {
    dest[i_dest] = src[i_src];
    ++i_dest;
    ++i_src;
  }
  dest[i_dest] = '\0';
  return dest;
}

const char* Strchr(const char* str, char symbol) {
  if (*str == symbol) {
    return str;
  }
  size_t i_str = 0;
  while (str[i_str] != symbol && str[i_str] != '\0') {
    ++i_str;
  }
  if (str[i_str] == symbol) {
    return str + i_str;
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  size_t i_str = Strlen(str);
  while (str[i_str] != symbol && i_str > 0) {
    i_str--;
  }
  if (str[i_str] == symbol) {
    return str + i_str;
  }
  return nullptr;
}

size_t Strspn(const char* dest, const char* src) {
  size_t i_dest = 0;
  size_t i_src = 0;
  size_t counter = 0;
  while (src[i_src] != '\0') {
    if (src[i_src] == dest[i_dest]) {
      ++i_dest;
      ++counter;
      i_src = 0;
    } else {
      ++i_src;
    }
  }
  return counter;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t i_dest = 0;
  size_t i_src = 0;
  size_t counter = 0;
  int flag = 0;
  while (dest[i_dest] != '\0' && flag == 0) {
    while (src[i_src] != '\0') {
      if (src[i_src] == dest[i_dest]) {
        flag = 1;
        break;
      }
      ++i_src;
    }
    if (src[i_src] == '\0') {
      ++counter;
      i_src = 0;
      ++i_dest;
    }
  }
  return counter;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  size_t i_breakset = 0;
  size_t i_dest = 0;
  int flag = 0;
  while (dest[i_dest] != '\0' && flag == 0) {
    while (breakset[i_breakset] != '\0') {
      if (breakset[i_breakset] == dest[i_dest]) {
        flag = 1;
        break;
      }
      ++i_breakset;
    }
    if (flag == 0) {
      ++i_dest;
      i_breakset = 0;
    }
  }
  if (flag == 1) {
    return dest + i_dest;
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  if (Strlen(pattern) == 0) {
    return str;
  }
  if (Strlen(pattern) > Strlen(str)) {
    return nullptr;
  }
  size_t i_str = 0;
  const char* pointer = nullptr;
  while (str[i_str] != '\0') {
    if (str[i_str] == pattern[0]) {
      pointer = str + i_str;
      size_t i_pattern = 1;
      while (pattern[i_pattern] != '\0') {
        if (i_str + i_pattern > Strlen(str) or str[i_str + i_pattern] != pattern[i_pattern]) {
          pointer = nullptr;
          break;
        }
        ++i_pattern;
      }
      if (pointer != nullptr) {
        return pointer;
      }
    }
    ++i_str;
  }
  return pointer;
}
