#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<size_t> > edges_;
  size_t quantity_vert_;

 public:
  size_t graph_components_ = 0;
  std::vector<std::string> colors_;
  std::vector<std::vector<size_t> > component_set_;
  std::vector<int64_t> parent_;
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
    component_set_.emplace_back();
    for (auto neighbor : edges_[begin_vertex]) {
      if (colors_[neighbor] == "white") {
        DfsVisit(neighbor);
      }
    }
    colors_[begin_vertex] = "black";
    component_set_[graph_components_].emplace_back(begin_vertex);
  }
};

int main() {
  size_t quantity_vertexes = 0;
  size_t quantity_pairs = 0;
  std::cin >> quantity_vertexes >> quantity_pairs;
  Graph graph(quantity_vertexes);
  size_t first_vert = 0;
  size_t second_vert = 0;
  for (size_t i = 1; i <= quantity_pairs; ++i) {
    std::cin >> first_vert >> second_vert;
    graph.PushEdge(first_vert, second_vert);
  }
  graph.DFS();
  std::cout << graph.graph_components_ << '\n';
  for (size_t i = 0; i < graph.graph_components_; ++i) {
    std::cout << graph.component_set_[i].size() << '\n';
    for (size_t j = 0; j < graph.component_set_[i].size(); ++j) {
      std::cout << graph.component_set_[i][j] << " ";
    }
    std::cout << '\n';
  }
}