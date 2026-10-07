#include <iostream>

struct Zero {
  static inline int key = 0;
  static inline int k1 = 4;
  static inline int k2 = 6;
  static inline int size = 2;
};
struct One {
  static inline int key = 1;
  static inline int k1 = 8;
  static inline int k2 = 6;
  static inline int size = 2;
};
struct Two {
  static inline int key = 2;
  static inline int k1 = 7;
  static inline int k2 = 9;
  static inline int size = 2;
};
struct Three {
  static inline int key = 3;
  static inline int k1 = 8;
  static inline int k2 = 4;
  static inline int size = 2;
};
struct Four {
  static inline int key = 4;
  static inline int k1 = 9;
  static inline int k2 = 3;
  static inline int k3 = 0;
  static inline int size = 3;
};
struct Six {
  static inline int key = 6;
  static inline int k1 = 7;
  static inline int k2 = 1;
  static inline int k3 = 0;
  static inline int size = 3;
};
struct Seven {
  static inline int key = 7;
  static inline int k1 = 2;
  static inline int k2 = 6;
  static inline int size = 2;
};
struct Eight {
  static inline int key = 8;
  static inline int k1 = 1;
  static inline int k2 = 3;
  static inline int size = 2;
};
struct Nine {
  static inline int key = 9;
  static inline int k1 = 2;
  static inline int k2 = 4;
  static inline int size = 2;
};

int Answer(int x, int& counter, int n) {
  if (n == 1) {
    return counter;
  }
  if (x == 0) {
    using Type = Zero;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    counter = counter - 1 + Type::size;
  } else if (x == 1) {
    using Type = One;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    counter = counter - 1 + Type::size;
  } else if (x == 2) {
    using Type = Two;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    counter = counter - 1 + Type::size;
  } else if (x == 3) {
    using Type = Three;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    counter = counter - 1 + Type::size;
  } else if (x == 4) {
    using Type = Four;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    Answer(Type::k3, counter, n - 1);
    counter = counter - 1 + Type::size;
  } else if (x == 6) {
    using Type = Six;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    Answer(Type::k3, counter, n - 1);
    counter = counter - 1 + Type::size;
  } else if (x == 7) {
    using Type = Seven;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    counter = counter - 1 + Type::size;
  } else if (x == 8) {
    using Type = Eight;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    counter = counter - 1 + Type::size;
  } else if (x == 9) {
    using Type = Nine;
    Answer(Type::k1, counter, n - 1);
    Answer(Type::k2, counter, n - 1);
    counter = counter - 1 + Type::size;
  }
  return counter;
}

int main() {
  int counter = 1;
  int answer = 0;
  int n = 0;
  std::cin >> n;
  if (n == 1) {
    std::cout << 8;
  } else {
    for (int i = 1; i < 8; ++i) {
      answer += Answer(i, counter, n);
      counter = 1;
    }
    answer += Answer(9, counter, n);
    std::cout << answer - 1;
  }
}