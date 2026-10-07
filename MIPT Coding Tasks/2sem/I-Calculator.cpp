#include <iostream>
#include <queue>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::priority_queue<int, std::vector<int>, std::greater<int> > coins;
  for (int i = 0; i < n; ++i) {
    int coin = 0;
    std::cin >> coin;
    coins.push(coin);
  }
  double ans = 0;
  while (coins.size() > 1) {
    int sum = coins.top();
    coins.pop();
    sum += coins.top();
    coins.pop();
    ans += sum * 0.05;
    coins.push(sum);
  }
  std::cout << ans;
}