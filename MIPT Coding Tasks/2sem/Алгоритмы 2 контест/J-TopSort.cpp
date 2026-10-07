#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<size_t> > edges_;
  size_t quantity_vert_;

 public:
  std::vector<std::string> colors_;
  std::vector<size_t> top_sort_;
  bool flag = true;
  explicit Graph(const size_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    colors_.resize(quantity_vert_ + 1, "white");
    edges_.resize(quantity_vert_ + 1);
  }
  void PushEdge(size_t first_vert, size_t second_vert) {
    edges_[first_vert].push_back(second_vert);
  }
  void DFS() {
    for (size_t i = 1; i <= quantity_vert_; ++i) {
      if (colors_[i] == "white") {
        if (!TopSortVisit(i)) {
          flag = false;
          return;
        }
      }
    }
  }
  bool TopSortVisit(size_t begin_vertex) {
    colors_[begin_vertex] = "gray";
    for (auto neighbor : edges_[begin_vertex]) {
      if (colors_[neighbor] == "gray") {
        return false;
      }
      if (colors_[neighbor] == "white") {
        if (!TopSortVisit(neighbor)) {
          return false;
        }
      }
    }
    colors_[begin_vertex] = "black";
    top_sort_.emplace_back(begin_vertex);
    return true;
  }
};

int main() {
  size_t quantity_vertexes = 0;
  size_t quantity_edges = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes);
  size_t first_vert = 0;
  size_t second_vert = 0;
  for (size_t i = 1; i <= quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert;
    graph.PushEdge(first_vert, second_vert);
  }
  graph.DFS();
  if (!graph.flag) {
    std::cout << -1;
  } else {
    for (size_t i = quantity_vertexes - 1; i > 0; --i) {
      std::cout << graph.top_sort_[i] << " ";
    }
    std::cout << graph.top_sort_[0];
  }
}