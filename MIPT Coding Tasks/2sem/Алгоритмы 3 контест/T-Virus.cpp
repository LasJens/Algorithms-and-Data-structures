#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class Graph {
 public:
  std::vector<std::vector<std::pair<int64_t, int64_t>>> vert_;
  std::priority_queue<std::pair<int64_t, int64_t>> queue_;
  std::vector<int64_t> parent_;
  std::vector<bool> is_used_;
  std::vector<int64_t> dist_;
  Graph(int64_t n, int64_t m) : vert_(n + 1), parent_(n + 1), is_used_(n + 1, false), dist_(n + 1, 30000000000000) {
    int64_t temp1 = 0;
    int64_t temp2 = 0;
    int64_t temp3 = 0;
    for (int64_t i = 0; i < m; ++i) {
      std::cin >> temp1 >> temp2 >> temp3;
      if (temp1 != temp2) {
        vert_[temp1].emplace_back(temp2, temp3);
        vert_[temp2].emplace_back(temp1, temp3);
      }
    }
  }
  void Dijkstra(int64_t verticle) {
    dist_[verticle] = 0;
    queue_.emplace(0, verticle);
    while (!queue_.empty()) {
      int64_t local_top = queue_.top().second;
      queue_.pop();
      if (!is_used_[local_top]) {
        is_used_[local_top] = true;
        for (size_t i = 0; i < vert_[local_top].size(); ++i) {
          int64_t to = vert_[local_top][i].first;
          int64_t len = vert_[local_top][i].second;
          if ((dist_[local_top] + len) < dist_[to]) {
            dist_[to] = dist_[local_top] + len;
            parent_[to] = local_top;
            queue_.emplace(-dist_[to], to);
          }
        }
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  int64_t k = 0;
  int64_t start = 0;
  int64_t finish = 0;
  std::cin >> n >> m >> k;
  std::vector<int64_t> ill(k);
  for (int64_t i = 0; i < k; ++i) {
    std::cin >> ill[i];
  }
  Graph graph(n, m);
  std::cin >> start >> finish;
  graph.Dijkstra(finish);
  for (int64_t j = 0; j < k; ++j) {
    if (graph.dist_[ill[j]] <= graph.dist_[start]) {
      std::cout << -1;
      return 0;
    }
  }
  std::cout << graph.dist_[start];
}