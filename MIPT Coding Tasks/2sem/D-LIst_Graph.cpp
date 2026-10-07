#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<std::vector<int> > graph;
  graph.resize(n);
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int type = 0;
    std::cin >> type;
    if (type == 1) {
      int u = 0;
      int v = 0;
      std::cin >> u >> v;
      graph[u - 1].push_back(v);
      graph[v - 1].push_back(u);
    } else {
      int u = 0;
      std::cin >> u;
      for (size_t j = 0; j < graph[u - 1].size(); ++j) {
        std::cout << graph[u - 1][j] << " ";
      }
      std::cout << '\n';
    }
  }
}