#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int64_t from_;
  int64_t to_;
  int64_t time_in_;
  int64_t time_out_;
  Edge(const int64_t& from, const int64_t& to, const int64_t& time_in, const int64_t& time_out)
      : from_(from), to_(to), time_in_(time_in), time_out_(time_out) {
  }
  Edge() = default;
};

bool operator<(const Edge& first, const Edge& second) {
  return first.time_in_ > second.time_in_;
}

class Graph {
 public:
  int64_t quantity_vertexes_;
  int64_t start_;
  int64_t finish_;
  std::vector<Edge> edges_;
  std::vector<int64_t> dist_;
  explicit Graph(int64_t quantity_vertexes, int64_t begin_vertex, int64_t end_vertex)
      : quantity_vertexes_(quantity_vertexes), start_(begin_vertex), finish_(end_vertex) {
    dist_.resize(quantity_vertexes_, 30000000000000);
  }
  void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& time_in,
                const int64_t& time_out) {
    edges_.emplace_back(first_vert, second_vert, time_in, time_out);
  }
  bool Relax(const Edge& edge) {
    if ((edge.time_in_ >= dist_[edge.from_]) && (edge.time_out_ < dist_[edge.to_])) {
      dist_[edge.to_] = edge.time_out_;
      return true;
    }
    return false;
  }
  void BellmanFord() {
    dist_[start_] = 0;
    std::sort(edges_.begin(), edges_.end());
    for (int64_t i = 0; i <= quantity_vertexes_; ++i) {
      for (auto& edge : edges_) {
        Relax(edge);
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  std::cin >> quantity_vertexes;
  int64_t begin_vertex = 0;
  int64_t end_vertex = 0;
  std::cin >> begin_vertex >> end_vertex;
  Graph graph(quantity_vertexes, begin_vertex - 1, end_vertex - 1);
  int64_t from = 0;
  int64_t to = 0;
  int64_t time_in = 0;
  int64_t time_out = 0;
  int64_t quantity_edges = 0;
  std::cin >> quantity_edges;
  for (int64_t i = 0; i < quantity_edges; ++i) {
    std::cin >> from >> time_in >> to >> time_out;
    graph.PushEdge(from - 1, to - 1, time_in, time_out);
  }
  graph.BellmanFord();
  std::cout << graph.dist_[graph.finish_];
}