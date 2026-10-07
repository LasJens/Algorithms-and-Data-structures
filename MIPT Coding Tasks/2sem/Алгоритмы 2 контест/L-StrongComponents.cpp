#include <iostream>
#include <algorithm>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<size_t> > edges_;
  std::vector<std::vector<size_t> > trans_edges_;
  size_t quantity_vert_;

 public:
  std::vector<std::string> colors1_;
  std::vector<std::string> colors2_;
  std::vector<size_t> numbers_;
  std::vector<std::vector<size_t> > components_;
  std::vector<size_t> top_sort_;
  size_t graph_components_ = 0;
  explicit Graph(const size_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    colors1_.resize(quantity_vert_ + 1, "white");
    colors2_.resize(quantity_vert_ + 1, "white");
    numbers_.resize(quantity_vert_ + 1, 0);
    edges_.resize(quantity_vert_ + 1);
    trans_edges_.resize(quantity_vert_ + 1);
  }
  void PushEdge(size_t first_vert, size_t second_vert) {
    edges_[first_vert].push_back(second_vert);
  }
  void TopSort() {
    for (size_t i = 1; i <= quantity_vert_; ++i) {
      if (colors1_[i] == "white") {
        TopSortVisit(i);
      }
    }
    std::reverse(top_sort_.begin(), top_sort_.end());
  }
  void TopSortVisit(size_t begin_vertex) {
    colors1_[begin_vertex] = "gray";
    for (auto neighbor : edges_[begin_vertex]) {
      if (colors1_[neighbor] == "white") {
        TopSortVisit(neighbor);
      }
    }
    colors1_[begin_vertex] = "black";
    top_sort_.emplace_back(begin_vertex);
  }
  void TranspositionGraph() {
    size_t old_vert = 0;
    for (size_t i = 1; i <= quantity_vert_; ++i) {
      while (!edges_[i].empty()) {
        old_vert = edges_[i][0];
        trans_edges_[old_vert].emplace_back(i);
        edges_[i].erase(edges_[i].begin());
      }
      edges_[i].reserve(0);
    }
  }
  void DFS() {
    for (size_t i = 0; i < quantity_vert_; ++i) {
      if (colors2_[top_sort_[i]] == "white") {
        components_.emplace_back();
        DfsVisit(top_sort_[i]);
        ++graph_components_;
      }
    }
  }
  void DfsVisit(size_t begin_vertex) {
    colors2_[begin_vertex] = "gray";
    for (auto neighbor : trans_edges_[begin_vertex]) {
      if (colors2_[neighbor] == "white") {
        DfsVisit(neighbor);
      }
    }
    colors2_[begin_vertex] = "black";
    components_[graph_components_].push_back(begin_vertex);
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
  graph.TopSort();
  graph.TranspositionGraph();
  graph.DFS();
  std::cout << graph.graph_components_ << '\n';
  for (size_t i = 0; i < graph.graph_components_; ++i) {
    for (size_t j = 0; j < graph.components_[i].size(); ++j) {
      graph.numbers_[graph.components_[i][j]] = i + 1;
    }
  }
  for (size_t i = 1; i <= quantity_vertexes; ++i) {
    std::cout << graph.numbers_[i] << ' ';
  }
}