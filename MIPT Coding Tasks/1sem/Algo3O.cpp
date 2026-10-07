#include <iostream>
#include <cstring>

struct Node {
  char key;
  Node* next = nullptr;
  Node* previous = nullptr;
};

struct Deque {
  size_t size = 0;
  Node* first = nullptr;
  Node* last = nullptr;
};

void PushBack(Deque* deque, char x) {
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
}

void PopFront(Deque* deque) {
  if (deque->size == 0) {
    return;
  }
  Node* node = deque->first;
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
}

void PopBack(Deque* deque) {
  if (deque->size == 0) {
    return;
  }
  Node* node = deque->last;
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

char Front(Deque* deque) {
  if (deque->size == 0) {
    return '0';
  }
  return deque->first->key;
}

char Back(Deque* deque) {
  if (deque->size == 0) {
    return '0';
  }
  return deque->last->key;
}

size_t Size(Deque* deque) {
  return deque->size;
}

void Clear(Deque* deque) {
  if (deque->first == nullptr) {
    return;
  }
  while (deque->first != nullptr) {
    PopFront(deque);
  }
}

int main() {
  auto deque = new Deque;
  char str[10001];
  std::cin.getline(str, 10001);
  int counter = 0;
  for (size_t i = 0; i < strlen(str); ++i) {
    PushBack(deque, str[i]);
  }
  while (true) {
    if (Size(deque) == 0) {
      std::cout << counter;
      break;
    }
    if (Front(deque) == Back(deque)) {
      PopFront(deque);
      PopBack(deque);
    } else {
      char b = Back(deque);
      PopBack(deque);
      if (Front(deque) == Back(deque)) {
        counter++;
      } else {
        PushBack(deque, b);
        PopFront(deque);
        if (Front(deque) == Back(deque)) {
          counter++;
        } else {
          PopBack(deque);
          counter += 2;
        }
      }
    }
  }
  Clear(deque);
  delete deque;
}
