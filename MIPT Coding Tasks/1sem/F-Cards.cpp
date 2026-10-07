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

int Front(Deque* deque) {
  if (deque->size == 0) {
    std::cout << "error" << '\n';
    return -1;
  }
  return deque->first->key;
}

int Back(Deque* deque) {
  if (deque->size == 0) {
    std::cout << "error" << '\n';
    return -1;
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
  auto hand_1 = new Deque;
  auto hand_2 = new Deque;
  char* cards_1 = new char[15];
  char* cards_2 = new char[15];
  std::cin.getline(cards_1, 15);
  std::cin.getline(cards_2, 15);
  int i = 0;
  while (cards_1[i] != '\0') {
    if (cards_1[i] != ' ') {
      PushBack(hand_1, cards_1[i] - '0');
    }
    ++i;
  }
  i = 0;
  while (cards_2[i] != '\0') {
    if (cards_2[i] != ' ') {
      PushBack(hand_2, cards_2[i] - '0');
    }
    ++i;
  }
  int round_counter = 0;
  while (round_counter < 1000000) {
    if (Size(hand_1) == 0) {
      std::cout << "second"
                << " ";
      break;
    }
    if (Size(hand_2) == 0) {
      std::cout << "first"
                << " ";
      break;
    }
    int fr_1 = Front(hand_1);
    int fr_2 = Front(hand_2);
    bool b = fr_1 == 9 && fr_2 == 0;
    if (((fr_1 > fr_2) && !b) || (fr_1 == 0 && fr_2 == 9)) {
      PopFront(hand_1);
      PopFront(hand_2);
      PushBack(hand_1, fr_1);
      PushBack(hand_1, fr_2);
    } else {
      PopFront(hand_1);
      PopFront(hand_2);
      PushBack(hand_2, fr_1);
      PushBack(hand_2, fr_2);
    }
    ++round_counter;
  }
  if (round_counter == 1000000) {
    std::cout << "botva";
  } else {
    std::cout << round_counter;
  }
  Clear(hand_1);
  Clear(hand_2);
  delete hand_1;
  delete hand_2;
  delete[] cards_1;
  delete[] cards_2;
}