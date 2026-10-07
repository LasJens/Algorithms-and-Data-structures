#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int64_t to_;
  int64_t weight_;
  Edge(const int64_t& to, const int64_t& weight) : to_(to), weight_(weight) {
  }
  Edge() = default;
};
class Graph {
 private:
  int64_t quantity_vertexes_;
  int64_t nights_;
  int64_t start_;
  int64_t finish_;
  std::vector<std::vector<Edge> > edges_;

 public:
  std::vector<std::vector<int64_t> > dist_;
  explicit Graph(int64_t quantity_vertexes, int64_t nights, int64_t start, int64_t finish)
      : quantity_vertexes_(quantity_vertexes), nights_(nights), start_(start), finish_(finish) {
    edges_.resize(quantity_vertexes_);
    dist_.resize(nights + 1);
    for (int64_t i = 0; i <= nights; ++i) {
      dist_[i].resize(quantity_vertexes_, 2000000000);
    }
  }
  void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    edges_[first_vert].emplace_back(second_vert, weight);
  }
  void Print() {
    int64_t min_weight = 2000000000;
    for (int64_t i = 0; i <= nights_; ++i) {
      if (dist_[i][finish_] < min_weight) {
        min_weight = dist_[i][finish_];
      }
    }
    if (min_weight == 2000000000) {
      min_weight = -1;
    }
    std::cout << min_weight;
  }
  bool Relax(int64_t k, int64_t from, const Edge& edge) {
    if (dist_[k + 1][edge.to_] > dist_[k][from] + edge.weight_) {
      dist_[k + 1][edge.to_] = dist_[k][from] + edge.weight_;
      return true;
    }
    return false;
  }
  void Bellman() {
    dist_[0][start_] = 0;
    std::vector<std::queue<int64_t> > queues;
    queues.resize(nights_ + 2);
    queues[0].push(start_);
    for (int64_t k = 0; (!queues[k].empty() && k < nights_); ++k) {
      bool is_change = false;
      while (!queues[k].empty()) {
        auto new_vert = queues[k].front();
        queues[k].pop();
        for (auto& edge : edges_[new_vert]) {
          if (Relax(k, new_vert, edge)) {
            queues[k + 1].push(edge.to_);
            is_change = true;
          }
        }
      }
      if (!is_change) {
        break;
      }
    }
  }
};
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  int64_t nights = 0;
  int64_t start = 0;
  int64_t finish = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  std::cin >> nights >> start >> finish;
  Graph graph(quantity_vertexes, nights, start - 1, finish - 1);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  int64_t weight = 0;
  for (int64_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert >> weight;
    graph.PushEdge(first_vert - 1, second_vert - 1, weight);
  }
  graph.Bellman();
  graph.Print();
}