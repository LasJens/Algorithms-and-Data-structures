#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 private:
  int64_t quantity_vert_;

 public:
  std::vector<std::vector<int64_t>> edges_;
  std::vector<std::string> colors_;
  std::vector<int64_t> parent_;
  int64_t graph_components_ = 0;
  int64_t has_cycle_ = false;
  explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    edges_.resize(quantity_vert_ + 1);
    colors_.resize(quantity_vert_ + 1, "white");
    parent_.resize(quantity_vert_ + 1);
  }
  void PushEdge(int64_t first_vert, int64_t second_vert) {
    edges_[first_vert].push_back(second_vert);
    edges_[second_vert].push_back(first_vert);
  }
  bool FindVertex(int64_t begin_vert, int64_t end_vert) {
    return (edges_[begin_vert].end() != std::find(edges_[begin_vert].begin(), edges_[begin_vert].end(), end_vert));
  }
  void DFS() {
    for (int64_t i = 1; i <= quantity_vert_; ++i) {
      if (colors_[i] == "white") {
        DfsVisit(i);
        ++graph_components_;
      }
    }
  }
  void DfsVisit(int64_t begin_vertex) {
    colors_[begin_vertex] = "gray";
    for (auto neighbor : edges_[begin_vertex]) {
      if (colors_[neighbor] == "white") {
        parent_[neighbor] = begin_vertex;
        DfsVisit(neighbor);
      } else if ((colors_[neighbor] == "gray") && (parent_[begin_vertex] != neighbor)) {
        has_cycle_ = true;
      }
    }
    colors_[begin_vertex] = "gray";
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  std::string atoms;
  std::cin >> quantity_vertexes >> quantity_edges;
  std::cin >> atoms;
  Graph graph(quantity_vertexes);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  for (int64_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert;
    if (((atoms[first_vert - 1] == 'H') && (atoms[second_vert - 1] == 'H')) || (first_vert == second_vert)) {
      std::cout << "NO";
      return 0;
    }
    if (graph.FindVertex(first_vert, second_vert)) {
      std::cout << "NO";
      return 0;
    }
    graph.PushEdge(first_vert, second_vert);
  }
  bool flag = true;
  for (int64_t i = 1; i <= quantity_vertexes; ++i) {
    if ((atoms[i - 1] == 'C') && (graph.edges_[i].size() != 4)) {
      flag = false;
    }
    if ((atoms[i - 1] == 'H') && (graph.edges_[i].size() != 1)) {
      flag = false;
    }
  }
  if (!flag) {
    std::cout << "NO";
    return 0;
  }
  graph.DFS();
  if ((graph.graph_components_ == 1) && (!graph.has_cycle_)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}