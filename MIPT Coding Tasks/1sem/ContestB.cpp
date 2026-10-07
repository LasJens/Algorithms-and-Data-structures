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

int Size(Deque* deque) {
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
  char str[100001];
  std::cin.getline(str, 100001);
  int flag = 0;
  char array[20];
  array[0] = 'b';
  array[1] = 'c';
  array[2] = 'd';
  array[3] = 'f';
  array[4] = 'g';
  array[5] = 'h';
  array[6] = 'j';
  array[7] = 'k';
  array[8] = 'l';
  array[9] = 'm';
  array[10] = 'n';
  array[11] = 'p';
  array[12] = 'q';
  array[13] = 'r';
  array[14] = 's';
  array[15] = 't';
  array[16] = 'v';
  array[17] = 'w';
  array[18] = 'x';
  array[19] = 'z';
  for (size_t i = 0; i < strlen(str); ++i) {
    for (int j = 0; j < 20; ++j) {
      if (str[i] == array[j]) {
        flag = 1;
      }
      if (flag == 1) {
        PushBack(deque, str[i]);
      }
      flag = 0;
    }
  }
  while (true) {
    if (Size(deque) == 0) {
      std::cout << "YES";
      break;
    }
    if(Front(deque) == Back(deque)) {
      PopFront(deque);
      PopBack(deque);
    } else {
      std::cout << "NO";
      break;
    }
  }
  Clear(deque);
  delete deque;
}
