#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <queue>

struct Edge {
  int64_t vert_;
  int64_t flow_;
  int64_t capacity_;
  int64_t i_back_edge;
  Edge(const int& to, const int& flow, const int64_t& capacity, const int64_t& index_back_edge)
      : vert_(to), flow_(flow), capacity_(capacity), i_back_edge(index_back_edge) {
  }
  Edge() = default;
};

struct BackEdge {
  int64_t vertex_;
  int64_t i_back_edge;
  BackEdge(const int64_t& vertex, const int64_t& index_back_edge) : vertex_(vertex), i_back_edge(index_back_edge) {
  }
  BackEdge() = default;
};

class Graph {
 public:
  int64_t quantity_vertexes_;
  int64_t max_flow_ = 0;
  std::vector<BackEdge> path_;
  std::vector<std::vector<Edge>> edges_;
  explicit Graph(int64_t quantity_vertexes) : quantity_vertexes_(quantity_vertexes), edges_(quantity_vertexes) {
  }
  void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    size_t index_back_edge = edges_[second_vert].size();
    edges_[first_vert].emplace_back(second_vert, 0, weight, index_back_edge);
    index_back_edge = edges_[first_vert].size() - 1;
    edges_[second_vert].emplace_back(first_vert, 0, 0, index_back_edge);
  }
  void EdmondsCarp() {
    path_.resize(quantity_vertexes_, {-1, -1});
    int64_t dif = BFSFlow(0);
    while (dif) {
      max_flow_ += dif;
      int64_t cur = quantity_vertexes_ - 1;
      int64_t i_cur_edge = 0;
      int64_t index_current_back_edge = 0;
      while (cur != 0) {
        i_cur_edge = path_[cur].i_back_edge;
        edges_[cur][i_cur_edge].flow_ -= dif;
        index_current_back_edge = edges_[cur][i_cur_edge].i_back_edge;
        cur = path_[cur].vertex_;
        edges_[cur][index_current_back_edge].flow_ += dif;
      }
      dif = BFSFlow(0);
    }
  }
  int64_t BFSFlow(const int& begin_vertex) {
    std::vector<bool> is_used;
    std::vector<int64_t> flows;
    is_used.resize(quantity_vertexes_, false);
    flows.resize(quantity_vertexes_, 0);
    std::queue<int64_t> queue;
    queue.push(begin_vertex);
    int64_t new_vertex = 0;
    flows[begin_vertex] = 30000000000000;
    while (!queue.empty()) {
      new_vertex = queue.front();
      queue.pop();
      for (auto& edge : edges_[new_vertex]) {
        if ((!is_used[edge.vert_]) && (edge.flow_ < edge.capacity_)) {
          if (std::min(edge.capacity_ - edge.flow_, flows[new_vertex]) > flows[edge.vert_]) {
            flows[edge.vert_] = std::min(edge.capacity_ - edge.flow_, flows[new_vertex]);
            is_used[edge.vert_] = true;
            path_[edge.vert_] = BackEdge(new_vertex, edge.i_back_edge);
            queue.push(edge.vert_);
          }
        }
      }
    }
    return flows[quantity_vertexes_ - 1];
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
  graph.EdmondsCarp();
  std::cout << graph.max_flow_;
}