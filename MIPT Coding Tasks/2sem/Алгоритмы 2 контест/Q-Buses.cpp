#include <iostream>
#include <vector>
#include <deque>

class Graph {
 private:
  std::vector<std::deque<int64_t> > edges_;
  int64_t quantity_vert_;

 public:
  std::vector<std::string> colors_;
  std::vector<bool> visited_;
  std::vector<int64_t> euler_cycle_;
  explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    edges_.resize(quantity_vert_ + 1);
    colors_.resize(quantity_vert_ + 1, "white");
    visited_.resize(quantity_vert_ + 1, false);
  }
  void PushEdge(int64_t first_vert, int64_t second_vert) {
    edges_[first_vert].push_back(second_vert);
    visited_[first_vert] = true;
    visited_[second_vert] = true;
  }
  void DFS() {
    for (int64_t i = 1; i <= quantity_vert_; ++i) {
      if ((colors_[i] == "white") && visited_[i]) {
        DfsVisit(i);
      }
    }
  }
  void DfsVisit(int64_t begin_vertex) {
    colors_[begin_vertex] = "gray";
    for (auto neighbor : edges_[begin_vertex]) {
      if (colors_[neighbor] == "white") {
        DfsVisit(neighbor);
      }
    }
    colors_[begin_vertex] = "black";
  }
  void DfsEulerCycle(int64_t parent, int64_t current_vert) {
    while (!edges_[current_vert].empty()) {
      size_t size = edges_[current_vert].size();
      if ((size != 1) && (edges_[current_vert][0] == parent)) {
        int64_t neighbor = edges_[current_vert][1];
        edges_[current_vert].erase(edges_[current_vert].begin() + 1);
        DfsEulerCycle(current_vert, neighbor);
      } else {
        int64_t neighbor = edges_[current_vert][0];
        edges_[current_vert].erase(edges_[current_vert].begin());
        DfsEulerCycle(current_vert, neighbor);
      }
    }
    euler_cycle_.emplace_back(current_vert);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_routs = 0;
  std::cin >> quantity_routs >> quantity_vertexes;
  Graph graph(quantity_vertexes);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  int64_t begin_vert = 0;
  int64_t k = 0;
  size_t counter = 0;
  if (quantity_routs == 0) {
    std::cout << 0;
    return 0;
  }
  for (int64_t i = 0; i < quantity_routs; ++i) {
    std::cin >> k;
    std::cin >> first_vert;
    counter += k;
    for (int64_t j = 0; j < k; ++j) {
      std::cin >> second_vert;
      graph.PushEdge(first_vert, second_vert);
      first_vert = second_vert;
    }
  }
  graph.DFS();
  for (int64_t i = 1; i <= quantity_vertexes; ++i) {
    if (graph.visited_[i]) {
      begin_vert = i;
      break;
    }
  }
  graph.DfsEulerCycle(-1, begin_vert);
  size_t size_new_path = graph.euler_cycle_.size();
  if ((size_new_path - 1) != counter) {
    std::cout << 0;
    return 0;
  }
  std::cout << size_new_path << ' ';
  for (size_t i = size_new_path - 1; i > 0; --i) {
    std::cout << graph.euler_cycle_[i] << ' ';
  }
  std::cout << graph.euler_cycle_[0];
}