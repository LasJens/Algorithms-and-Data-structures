#include <iostream>

struct Node {
  int key;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

Node* Insert(Node* node, int x) {
  if (node->key == x) {
    return node;
  }
  if (node->key < x) {
    if (node->right == nullptr) {
      node->right = new Node;
      node->right->key = x;
      node->right->parent = node;
    } else {
      node->right = Insert(node->right, x);
    }
  } else {
    if (node->left == nullptr) {
      node->left = new Node;
      node->left->key = x;
      node->left->parent = node;
    } else {
      node->left = Insert(node->left, x);
    }
  }
  return node;
}

int HeightOfTree(Node* root) {
  if (root == nullptr) {
    return 0;
  }
  int h_1 = HeightOfTree(root->left);
  int h_2 = HeightOfTree(root->right);
  return h_1 > h_2 ? h_1 + 1 : h_2 + 1;
}

void PostorderTraversalClear(Node* x) {
  if (x != nullptr) {
    PostorderTraversalClear(x->left);
    PostorderTraversalClear(x->right);
    delete x;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Node* root = new Node;
  std::cin >> root->key;
  while (true) {
    int x = 0;
    std::cin >> x;
    if (x == 0) {
      break;
    }
    Insert(root, x);
  }
  std::cout << HeightOfTree(root);
  PostorderTraversalClear(root);
}