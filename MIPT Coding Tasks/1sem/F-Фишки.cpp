#include <iostream>
void AddChip(int n);
void DeleteChip(int n);

void AddChip(int n) {
  if (n == 1) {
    std::cout << 1 << " ";
  } else {
    AddChip(n - 1);
    std::cout << n << " ";
    DeleteChip(n - 1);
  }
}

void DeleteChip(int n) {
  if (n == 1) {
    std::cout << -1 << " ";
  } else {
    AddChip(n - 1);
    std::cout << -n << " ";
    DeleteChip(n - 1);
  }
}

int main() {
  int n;
  std::cin >> n;
  if (n == 1) {
    std::cout << 1;
  } else if (n == 2) {
    std::cout << 1 << " " << 2;
  } else if (n == 3) {
    std::cout << 1 << " " << 2 << " " << -1 << " " << 3 << " " << 1;
  } else if (n == 4) {
    AddChip(3);
    std::cout << 4 << " " << 1 << " " << 2;
  } else if (n == 5) {
    AddChip(4);
    std::cout << 5 << " " << 1 << " " << 2 << " " << -1 << " " << 3 << " " << 1;
  } else if (n == 6) {
    AddChip(5);
    std::cout << 6 << " ";
    AddChip(3);
    std::cout << 4 << " " << 1 << " " << 2;
  } else if (n == 7) {
    AddChip(6);
    std::cout << 7 << " ";
    AddChip(4);
    std::cout << 5 << " " << 1 << " " << 2 << " " << -1 << " " << 3 << " " << 1;
  } else if (n == 8) {
    AddChip(7);
    std::cout << 8 << " ";
    AddChip(5);
    std::cout << 6 << " ";
    AddChip(3);
    std::cout << 4 << " " << 1 << " " << 2;
  } else if (n == 9) {
    AddChip(8);
    std::cout << 9 << " ";
    AddChip(6);
    std::cout << 7 << " ";
    AddChip(4);
    std::cout << 5 << " " << 1 << " " << 2 << " " << -1 << " " << 3 << " " << 1;
  } else if (n == 10) {
    AddChip(9);
    std::cout << 10 << " ";
    AddChip(7);
    std::cout << 8 << " ";
    AddChip(5);
    std::cout << 6 << " ";
    AddChip(3);
    std::cout << 4 << " " << 1 << " " << 2;
  }
}
