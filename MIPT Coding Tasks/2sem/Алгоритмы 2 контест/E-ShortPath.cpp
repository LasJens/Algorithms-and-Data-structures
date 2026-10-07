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
  Graph(const size_t new_quantity_vert, const size_t new_begin_vertex, const size_t new_end_vertex)
      : quantity_vert_(new_quantity_vert), begin_vertex_(new_begin_vertex), end_vertex_(new_end_vertex) {
    edges_.resize(quantity_vert_ + 1);
    dist_.resize(quantity_vert_ + 1);
  }
  void PushEdge(size_t first_vert, size_t second_vert, size_t weight) {
    if (weight == 1) {
      edges_[first_vert].push_back(second_vert);
      return;
    }
    size_t old_size = edges_.size();
    size_t new_size = old_size + weight - 1;
    edges_.resize(new_size);
    dist_.resize(new_size, 0);
    edges_[first_vert].push_back(old_size);
    quantity_vert_ += weight - 1;
    for (size_t i = old_size; i < new_size - 1; ++i) {
      edges_[i].push_back(i + 1);
    }
    edges_[new_size - 1].push_back(second_vert);
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
  size_t weight = 0;
  for (size_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert >> weight;
    graph.PushEdge(first_vert, second_vert, weight);
  }
  graph.BFS();
  if ((graph.dist_[end_vertex] == 0) && (begin_vertex != end_vertex)) {
    std::cout << -1;
  } else if (begin_vertex == end_vertex) {
    std::cout << 0;
    std::cout << begin_vertex;
  } else {
    std::cout << graph.dist_[end_vertex];
  }
}