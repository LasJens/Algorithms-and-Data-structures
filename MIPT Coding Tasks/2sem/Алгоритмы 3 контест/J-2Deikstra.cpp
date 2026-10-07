#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  int64_t vert_;
  int64_t weight_;
  Edge(const int64_t& vert, const int64_t& weight) : vert_(vert), weight_(weight) {
  }
  Edge() = default;
};

class Graph {
 private:
  std::vector<std::vector<Edge> > vert_;
  int64_t quantity_vert_;

 public:
  std::vector<int64_t> dist_;
  std::vector<int64_t> parent_;
  std::vector<bool> is_used_;
  std::priority_queue<std::pair<int64_t, int64_t> > queue_;
  Graph() = default;
  explicit Graph(const int64_t& new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    vert_.resize(quantity_vert_ + 1);
    dist_.resize(quantity_vert_ + 1, 3000000000);
    parent_.resize(quantity_vert_ + 1);
    is_used_.resize(quantity_vert_ + 1);
  }
  void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
    vert_[first_vert].emplace_back(second_vert, weight);
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
          int64_t to = vert_[local_top][i].vert_;
          int64_t len = vert_[local_top][i].weight_;
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
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t start = 0;
  int64_t finish = 0;
  std::cin >> quantity_vertexes >> start >> finish;
  Graph graph(quantity_vertexes);
  int64_t weight = 0;
  for (int64_t i = 0; i < quantity_vertexes; ++i) {
    for (int64_t j = 0; j < quantity_vertexes; ++j) {
      std::cin >> weight;
      if (-1 == weight || i == j) {
        continue;
      }
      graph.PushEdge(i, j, weight);
    }
  }
  graph.Dijkstra(start - 1);
  if (graph.dist_[finish - 1] == 3000000000) {
    std::cout << -1;
    return 0;
  }
  std::cout << graph.dist_[finish - 1];
}