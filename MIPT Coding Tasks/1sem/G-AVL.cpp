#include <iostream>

struct Node {
  int key;
  int height = 1;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

class AVLTree {
  Node* top_;

 public:
  AVLTree() {
    top_ = nullptr;
  }

  void Insert(int x) {
    top_ = MyInsert(top_, x);
  }

  int Find(int x) {
    Node* ans = MyFind(top_, x);
    if (ans != nullptr) {
      return ans->key;
    }
    return -1;
  }

  void Output() {
    MyOutput(top_);
  }

  void Clear() {
    MyClear(top_);
  }

 private:
  int Height(Node* node) {
    int height = 0;
    if (node != nullptr) {
      height = node->height;
    }
    return height;
  }

  int BFactor(Node* p) {
    return Height(p->right) - Height(p->left);
  }

  void FixHeight(Node* node) {
    if (node == nullptr) {
      return;
    }
    int h_left = Height(node->left);
    int h_right = Height(node->right);
    node->height = h_left > h_right ? h_left + 1 : h_right + 1;
  }

  Node* RotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    FixHeight(p);
    FixHeight(q);
    return q;
  }

  Node* RotateLeft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    FixHeight(q);
    FixHeight(p);
    return p;
  }

  Node* Balance(Node* p) {
    FixHeight(p);
    if (BFactor(p) == 2) {
      if (BFactor(p->right) < 0) {
        p->right = RotateRight(p->right);
      }
      return RotateLeft(p);
    }
    if (BFactor(p) == -2) {
      if (BFactor(p->left) > 0) {
        p->left = RotateLeft(p->left);
      }
      return RotateRight(p);
    }
    return p;
  }

  Node* MyInsert(Node* node, int x) {
    if (node == nullptr) {
      node = new Node;
      node->key = x;
      return node;
    }
    if (node->key == x) {
      return node;
    }
    if (node->key < x) {
      if (node->right == nullptr) {
        node->right = new Node;
        node->right->key = x;
        node->right->parent = node;
      } else {
        node->right = MyInsert(node->right, x);
      }
    } else {
      if (node->left == nullptr) {
        node->left = new Node;
        node->left->key = x;
        node->left->parent = node;
      } else {
        node->left = MyInsert(node->left, x);
      }
    }
    return Balance(node);
  }

  Node* MyFind(Node* node, int x) {
    if (node == nullptr || node->key == x) {
      return node;
    }
    if (node->key < x) {
      return MyFind(node->right, x);
    }
    Node* found = MyFind(node->left, x);
    if (found == nullptr) {
      return node;
    }
    return found;
  }

  void MyOutput(Node* node) {
    if (node == nullptr) {
      return;
    }
    MyOutput(node->left);
    MyOutput(node->right);
    std::cout << node->key << " ";
  }

  void MyClear(Node* node) {
    if (node == nullptr) {
      return;
    }
    MyClear(node->left);
    MyClear(node->right);
    delete node;
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  int flag = 0;
  int previous = 0;
  AVLTree tree;
  for (int i = 0; i < n; ++i) {
    // tree.Output();
    char action = '0';
    std::cin >> action;
    int x = 0;
    std::cin >> x;
    if (action == '+' && flag == 0) {
      tree.Insert(x);
    } else if (action == '+' && flag == 1) {
      flag = 0;
      tree.Insert((x + previous) % 1000000000);
    } else {
      flag = 1;
      previous = tree.Find(x);
      std::cout << tree.Find(x) << '\n';
    }
  }
  tree.Clear();
}