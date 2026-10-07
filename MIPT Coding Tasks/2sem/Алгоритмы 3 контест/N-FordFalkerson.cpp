#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int64_t vert_;
  int64_t flow_;
  int64_t capacity_;
  int64_t i_back_edge_;
  Edge(const int& to, const int& flow, const int64_t& capacity, const int64_t& index_back_edge)
      : vert_(to), flow_(flow), capacity_(capacity), i_back_edge_(index_back_edge) {
  }
  Edge() = default;
};

class Graph {
 public:
  int64_t quantity_vertexes_;
  int64_t max_flow_ = 0;
  int64_t time_ = 1;
  std::vector<int64_t> is_used_;
  std::vector<std::vector<Edge>> edges_;
  explicit Graph(int64_t quantity_vertexes)
      : quantity_vertexes_(quantity_vertexes), is_used_(quantity_vertexes), edges_(quantity_vertexes) {
  }
  void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    size_t index_back_edge = edges_[second_vert].size();
    edges_[first_vert].emplace_back(second_vert, 0, weight, index_back_edge);
    index_back_edge = edges_[first_vert].size() - 1;
    edges_[second_vert].emplace_back(first_vert, 0, 0, index_back_edge);
  }
  void FordFalkerson() {
    int64_t dif = DFSFlow(0, 300000000);
    while (dif) {
      max_flow_ += dif;
      time_++;
      dif = DFSFlow(0, 300000000);
    }
  }
  int64_t DFSFlow(const int64_t& begin_vertex, const int64_t& cur_flow) {
    if (begin_vertex == quantity_vertexes_ - 1) {
      return cur_flow;
    }
    is_used_[begin_vertex] = time_;
    for (auto& edge : edges_[begin_vertex]) {
      if ((is_used_[edge.vert_] != time_) && (edge.flow_ < edge.capacity_)) {
        int64_t dif = DFSFlow(edge.vert_, std::min(cur_flow, edge.capacity_ - edge.flow_));
        if (dif > 0) {
          edge.flow_ += dif;
          edges_[edge.vert_][edge.i_back_edge_].flow_ -= dif;
          return dif;
        }
      }
    }
    return 0;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes);
  int64_t first_vertex = 0;
  int64_t second_vertex = 0;
  int64_t capacity = 0;
  for (int64_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vertex >> second_vertex >> capacity;
    graph.PushEdge(first_vertex - 1, second_vertex - 1, capacity);
  }
  graph.FordFalkerson();
  std::cout << graph.max_flow_;
}