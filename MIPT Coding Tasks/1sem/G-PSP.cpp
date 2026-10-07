#include <iostream>
#include <cstring>

struct Node {
  char key;
  Node* next = nullptr;
  Node* previous = nullptr;
};

struct Stack {
  size_t size = 0;
  Node* first = nullptr;
};

void Push(Stack* stack, char x) {
  Node* node = new Node;
  node->key = x;
  if (stack->size == 0) {
    stack->first = node;
  } else {
    node->previous = stack->first;
    stack->first = node;
    stack->first->next = node;
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

char Front(Stack* stack) {
  if (stack->size == 0) {
    return 'E';
  }
  return stack->first->key;
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

int main() {
  auto stack = new Stack;
  char s[100001];
  s[0] = '1';
  std::cin >> s;
  size_t i = 0;
  while (s[i] == '(' || s[i] == ')' || s[i] == '{' || s[i] == '}' || s[i] == '[' || s[i] == ']') {
    if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
      Push(stack, s[i]);
    } else {
      if (s[i] == ')' && Size(stack) > 0 && Front(stack) == '(') {
        Pop(stack);
      } else if (s[i] == '}' && Size(stack) > 0 && Front(stack) == '{') {
        Pop(stack);
      } else if (s[i] == ']' && Size(stack) > 0 && Front(stack) == '[') {
        Pop(stack);
      } else if (s[i] == '}' && (Size(stack) == 0 || Front(stack) == '(' || Front(stack) == '[')) {
        Push(stack, '1');
        break;
      } else if (s[i] == ')' && (Size(stack) == 0 || Front(stack) == '[' || Front(stack) == '{')) {
        Push(stack, '1');
        break;
      } else if (s[i] == ']' && (Size(stack) == 0 || Front(stack) == '{' || Front(stack) == '(')) {
        Push(stack, '1');
        break;
      }
    }
    ++i;
  }
  if (Size(stack) == 0 || s[0] == '1') {
    std::cout << "YES\n";
  } else {
    Clear(stack);
    std::cout << "NO\n";
  }
  delete stack;
}