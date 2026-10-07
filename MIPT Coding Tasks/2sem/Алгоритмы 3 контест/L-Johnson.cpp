#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>

struct Edge {
  int64_t from_;
  int64_t to_;
  int64_t weight_;
  Edge(int64_t from, int64_t to, int64_t weight) : from_(from), to_(to), weight_(weight) {
  }
  Edge() = default;
};

class Graph {
 private:
  std::vector<std::pair<int64_t, std::vector<Edge>>> array_;
  std::vector<Edge> edges_;
  int64_t size_;
  std::vector<int64_t> dist_;
  int64_t max_dist_ = -1;

 public:
  explicit Graph(int64_t quantity_vertex)
      : array_(quantity_vertex + 1), size_(quantity_vertex + 1), dist_(quantity_vertex + 1, 30000000) {
    for (int64_t i = 0; i < quantity_vertex; ++i) {
      array_[i].first = i;
    }
  }
  void PushEdge(int64_t from, int64_t to, int64_t weight) {
    edges_.emplace_back(from, to, weight);
  }
  void Bellman(int64_t start) {
    dist_[start] = 0;
    for (int64_t i = 0; i < size_ - 1; ++i) {
      for (auto edge : edges_) {
        if (dist_[edge.to_] > dist_[edge.from_] + edge.weight_) {
          dist_[edge.to_] = dist_[edge.from_] + edge.weight_;
        }
      }
    }
  }
  void Johnson() {
    Bellman(size_ - 1);
    for (auto edge : edges_) {
      edge.weight_ += (dist_[edge.from_] - dist_[edge.to_]);
      array_[edge.from_].second.emplace_back(edge.from_, edge.to_, edge.weight_);
    }
    for (int64_t i = 0; i < size_ - 1; ++i) {
      Dijkstra(i);
    }
    std::cout << max_dist_;
  }
  void Dijkstra(int64_t start) {
    std::vector<int64_t> dijkstra_dist(size_, 30000000);
    dijkstra_dist[start] = 0;
    std::vector<int64_t> prev(size_, -1);
    std::set<std::pair<int64_t, int64_t>> heap;
    for (int64_t i = 0; i < size_ - 1; ++i) {
      heap.emplace(dijkstra_dist[i], i);
    }
    while (!heap.empty()) {
      int64_t local = std::get<1>(*(heap.begin()));
      heap.erase(heap.begin());
      for (auto edge : array_[local].second) {
        std::pair<int64_t, int64_t> pair(dijkstra_dist[edge.to_], edge.to_);
        if (heap.find(pair) != heap.end() && edge.weight_ + dijkstra_dist[local] < dijkstra_dist[edge.to_]) {
          prev[edge.to_] = local;
          dijkstra_dist[edge.to_] = edge.weight_ + dijkstra_dist[local];
          heap.erase(pair);
          heap.emplace(edge.weight_ + dijkstra_dist[local], edge.to_);
        }
      }
    }
    for (int64_t i = 0; i < size_ - 1; ++i) {
      if (start != i && dijkstra_dist[i] < 30000000 && dijkstra_dist[i] - dist_[start] + dist_[i] > max_dist_) {
        max_dist_ = dijkstra_dist[i] - dist_[start] + dist_[i];
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  int64_t weight = 0;
  for (int64_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert >> weight;
    graph.PushEdge(first_vert, second_vert, weight);
  }
  for (int64_t i = 0; i < quantity_vertexes; ++i) {
    graph.PushEdge(quantity_vertexes, i, 0);
  }
  graph.Johnson();
}