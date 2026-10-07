#include <iostream>
#include <cstring>

struct Node {
  int key;
  Node* next = nullptr;
  Node* previous = nullptr;
};

struct Stack {
  size_t size = 0;
  Node* first = nullptr;
};

void Push(Stack* stack, int x) {
  Node* node = new Node;
  node->key = x;
  if (stack->size == 0) {
    stack->first = node;
  } else {
    node->previous = stack->first;
    stack->first = node;
    // stack->first->next = node (?)
  }
  ++stack->size;
}

void Pop(Stack* stack) {
  if (stack->size == 0) {
    return;
  }
  Node* node = stack->first;
  if (stack->size == 1) {
    delete node;
    stack->first = nullptr;
  } else {
    stack->first = stack->first->previous;
    delete node;
  }
  --stack->size;
}

int Front(Stack* stack) {
  if (stack->size == 0) {
    return 'E';
  }
  return stack->first->key;
}

int SecondFront(Stack* stack) {
  if (stack->size == 0 || stack->size == 1) {
    return 'E';
  }
  return stack->first->previous->key;
}

size_t Size(Stack* stack) {
  return stack->size;
}

void Clear(Stack* stack) {
  if (stack->first == nullptr) {
    return;
  }
  while (stack->first != nullptr) {
    Pop(stack);
  }
}

void Output(Stack* stack) {
  if (stack->first == nullptr) {
    return;
  }
  while (stack->first != nullptr) {
    std::cout << stack->first->key << " ";
    stack->first = stack->first->previous;
  }
}

int main() {
  auto stack = new Stack;
  char* x = new char[1000001];
  std::cin.getline(x, 1000001);
  int i = 0;
  while (x[i] != '\0') {
    if (x[i] != '+' && x[i] != '-' && x[i] != '*' && x[i] != ' ') {
      int n = x[i] - '0';
      Push(stack, n);
    } else if (x[i] == '+') {
      int y = Front(stack) + SecondFront(stack);
      Pop(stack);
      Pop(stack);
      Push(stack, y);
    } else if (x[i] == '-') {
      int y = SecondFront(stack) - Front(stack);
      Pop(stack);
      Pop(stack);
      Push(stack, y);
    } else if (x[i] == '*') {
      int y = Front(stack) * SecondFront(stack);
      Pop(stack);
      Pop(stack);
      Push(stack, y);
    }
    ++i;
  }
  std::cout << Front(stack);
  Clear(stack);
  delete stack;
  delete[] x;
}