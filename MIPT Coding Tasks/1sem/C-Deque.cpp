#include <iostream>
#include <cstring>

struct Node {
  int key;
  Node* next = nullptr;
  Node* previous = nullptr;
};

struct Deque {
  size_t size = 0;
  Node* first = nullptr;
  Node* last = nullptr;
};

void PushFront(Deque* deque, int x) {
  Node* node = new Node;
  node->key = x;
  if (deque->size == 0) {
    deque->first = node;
    deque->last = node;
  } else if (deque->size == 1) {
    node->previous = deque->last;
    deque->first = node;
    deque->last->next = deque->first;
  } else {
    node->previous = deque->first;
    deque->first->next = node;
    deque->first = node;
  }
  ++deque->size;
  std::cout << "ok" << '\n';
}

void PushBack(Deque* deque, int x) {
  Node* node = new Node;
  node->key = x;
  if (deque->size == 0) {
    deque->first = node;
    deque->last = node;
  } else if (deque->size == 1) {
    node->next = deque->first;
    deque->last = node;
    deque->first->previous = deque->last;
  } else {
    node->next = deque->last;
    deque->last->previous = node;
    deque->last = node;
  }
  ++deque->size;
  std::cout << "ok" << '\n';
}

int PopFront(Deque* deque) {
  if (deque->size == 0) {
    return 33333;
  }
  Node* node = deque->first;
  const int ans = deque->first->key;
  if (deque->size == 1) {
    delete node;
    deque->first = nullptr;
    deque->last = nullptr;
  } else {
    deque->first = deque->first->previous;
    deque->first->next = nullptr;
    delete node;
  }
  --deque->size;
  return ans;
}

void PopBack(Deque* deque) {
  if (deque->size == 0) {
    std::cout << "error" << '\n';
    return;
  }
  Node* node = deque->last;
  std::cout << deque->last->key << '\n';
  if (deque->size == 1) {
    delete node;
    deque->first = nullptr;
    deque->last = nullptr;
  } else {
    deque->last = deque->last->next;
    deque->last->previous = nullptr;
    delete node;
  }
  --deque->size;
}

void Front(Deque* deque) {
  if (deque->size == 0) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << deque->first->key << '\n';
}

void Back(Deque* deque) {
  if (deque->size == 0) {
    std::cout << "error" << '\n';
    return;
  }
  std::cout << deque->last->key << '\n';
}

void Size(Deque* deque) {
  std::cout << deque->size << '\n';
}

void Clear(Deque* deque) {
  if (deque->first == nullptr) {
    return;
  }
  while (deque->first != nullptr) {
    PopFront(deque);
  }
}

void Exit() {
  std::cout << "bye";
}

int main() {
  int k = 0;
  std::cin >> k;
  auto deque = new Deque;
  char str[11];
  for (int i = 0; i < k; ++i) {
    std::cin >> str;
    if (std::strcmp(str, "push_front") == 0) {
      int x = 0;
      std::cin >> x;
      PushFront(deque, x);
    } else if (std::strcmp(str, "push_back") == 0) {
      int x = 0;
      std::cin >> x;
      PushBack(deque, x);
    } else if (std::strcmp(str, "pop_front") == 0) {
      int current = PopFront(deque);
      if (current == 33333) {
        std::cout << "error" << '\n';
      } else {
        std::cout << current << '\n';
      }
    } else if (std::strcmp(str, "pop_back") == 0) {
      PopBack(deque);
    } else if (std::strcmp(str, "front") == 0) {
      Front(deque);
    } else if (std::strcmp(str, "back") == 0) {
      Back(deque);
    } else if (std::strcmp(str, "size") == 0) {
      Size(deque);
    } else if (std::strcmp(str, "clear") == 0) {
      Clear(deque);
      std::cout << "ok" << '\n';
    } else if (std::strcmp(str, "exit") == 0) {
      std::cout << "bye";
      break;
    }
  }
  Clear(deque);
  delete deque;
}
