#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<size_t> > edges_;
  size_t quantity_vert_;

 public:
  std::vector<std::string> colors_;
  std::vector<size_t> parent_;
  size_t vert_cycle_ = 0;
  explicit Graph(const size_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    edges_.resize(quantity_vert_ + 1);
    colors_.resize(quantity_vert_ + 1, "white");
    parent_.resize(quantity_vert_ + 1);
  }
  void PushEdge(size_t first_vert, size_t second_vert) {
    edges_[first_vert].push_back(second_vert);
  }
  bool HasCycle(size_t begin_vertex) {
    colors_[begin_vertex] = "gray";
    for (auto neighbor : edges_[begin_vertex]) {
      parent_[neighbor] = begin_vertex;
      if (colors_[neighbor] == "gray") {
        vert_cycle_ = neighbor;
        return true;
      }
      if (colors_[neighbor] == "white") {
        if (HasCycle(neighbor)) {
          return true;
        }
      }
    }
    colors_[begin_vertex] = "black";
    return false;
  }
  bool GraphHasCycle() {
    for (size_t i = 1; i <= quantity_vert_; ++i) {
      if (colors_[i] == "white") {
        if (HasCycle(i)) {
          return true;
        }
      }
    }
    return false;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t quantity_edges = 0;
  size_t quantity_vertexes = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes);
  size_t first_vert = 0;
  size_t second_vert = 0;
  for (size_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert;
    graph.PushEdge(first_vert, second_vert);
  }
  if (!graph.GraphHasCycle()) {
    std::cout << "NO";
  } else {
    std::cout << "YES" << '\n';
    std::vector<size_t> cycle;
    size_t start = graph.vert_cycle_;
    cycle.emplace_back(start);
    for (size_t i = graph.parent_[start]; i != start; i = graph.parent_[i]) {
      cycle.emplace_back(i);
    }
    for (size_t i = cycle.size() - 1; i > 0; --i) {
      std::cout << cycle[i] << ' ';
    }
    std::cout << cycle[0];
  }
}