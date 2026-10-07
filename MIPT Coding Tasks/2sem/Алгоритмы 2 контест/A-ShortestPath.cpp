#include <iostream>
#include <vector>
#include <queue>

class Graph {
 private:
  std::vector<std::vector<size_t> > edges_;
  size_t quantity_vert_;

 public:
  size_t begin_vertex_;
  size_t end_vertex_;
  std::vector<size_t> dist_;
  std::vector<size_t> parent_;
  Graph(const size_t new_quantity_vert, const size_t new_begin_vertex, const size_t new_end_vertex)
      : quantity_vert_(new_quantity_vert), begin_vertex_(new_begin_vertex), end_vertex_(new_end_vertex) {
    edges_.resize(quantity_vert_ + 1);
    dist_.resize(quantity_vert_ + 1);
    parent_.resize(quantity_vert_ + 1);
  }
  void PushEdge(size_t first_vert, size_t second_vert) {
    edges_[first_vert].push_back(second_vert);
    edges_[second_vert].push_back(first_vert);
  }
  void BFS() {
    std::queue<size_t> queue;
    queue.push(begin_vertex_);
    dist_[begin_vertex_] = 0;
    size_t new_vertex = 0;
    while (!queue.empty()) {
      new_vertex = queue.front();
      queue.pop();
      for (auto neighbor : edges_[new_vertex]) {
        if (dist_[neighbor] == 0) {
          dist_[neighbor] = dist_[new_vertex] + 1;
          parent_[neighbor] = new_vertex;
          queue.push(neighbor);
        }
      }
    }
  }
};

int main() {
  size_t quantity_edges = 0;
  size_t quantity_vertexes = 0;
  size_t begin_vertex = 0;
  size_t end_vertex = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  std::cin >> begin_vertex >> end_vertex;
  Graph graph(quantity_vertexes, begin_vertex, end_vertex);
  size_t first_vert = 0;
  size_t second_vert = 0;
  for (size_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert;
    graph.PushEdge(first_vert, second_vert);
  }
  graph.BFS();
  if ((graph.dist_[end_vertex] == 0) && (begin_vertex != end_vertex)) {
    std::cout << -1 << '\n';
  } else if (begin_vertex == end_vertex) {
    std::cout << 0 << '\n';
    std::cout << begin_vertex;
  } else {
    std::cout << graph.dist_[end_vertex] << '\n';
    std::vector<size_t> path;
    path.push_back(end_vertex);
    for (size_t i = graph.parent_[end_vertex]; i != begin_vertex; i = graph.parent_[i]) {
      path.push_back(i);
    }
    path.push_back(begin_vertex);
    for (size_t i = path.size() - 1; i > 0; --i) {
      std::cout << path[i] << ' ';
    }
    std::cout << path[0];
  }
}