#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<size_t> > edges_;
  size_t quantity_vert_;

 public:
  size_t graph_components_ = 0;
  std::vector<std::string> colors_;
  std::vector<size_t> parent_;
  explicit Graph(const size_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    edges_.resize(quantity_vert_ + 1);
    colors_.resize(quantity_vert_ + 1, "white");
  }
  void PushEdge(size_t first_vert, size_t second_vert) {
    edges_[first_vert].push_back(second_vert);
    edges_[second_vert].push_back(first_vert);
  }
  void DFS() {
    for (size_t i = 1; i <= quantity_vert_; ++i) {
      if (colors_[i] == "white") {
        DfsVisit(i);
        ++graph_components_;
      }
    }
  }
  void DfsVisit(size_t begin_vertex) {
    colors_[begin_vertex] = "gray";
    for (auto neighbor : edges_[begin_vertex]) {
      if (colors_[neighbor] == "white") {
        DfsVisit(neighbor);
      }
    }
    colors_[begin_vertex] = "black";
  }
};

int main() {
  size_t quantity_vertexes = 0;
  std::cin >> quantity_vertexes;
  Graph graph(quantity_vertexes);
  size_t first_vert = 0;
  for (size_t i = 1; i <= quantity_vertexes; ++i) {
    std::cin >> first_vert;
    graph.PushEdge(first_vert, i);
  }
  graph.DFS();
  std::cout << graph.graph_components_;
}