#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Graph {
 private:
  std::vector<std::vector<size_t> > edges_;
  size_t quantity_vert_;
  size_t param_;

 public:
  std::vector<std::string> colors_;
  std::set<size_t> articulation_points_;
  std::vector<size_t> time_in_;
  std::vector<size_t> time_up_;
  size_t time_ = 0;
  std::vector<size_t> n_children_;
  explicit Graph(const size_t new_quantity_vert, const size_t new_quantity_edges)
      : quantity_vert_(new_quantity_vert), param_(new_quantity_vert + new_quantity_edges) {
    edges_.resize(param_ + 1);
    colors_.resize(param_ + 1, "white");
    time_in_.resize(param_ + 1, -1);
    time_up_.resize(param_ + 1, -1);
    n_children_.resize(param_ + 1, 0);
  }
  void PushEdge(size_t first_vert, size_t second_vert, size_t third_vert, size_t addition) {
    edges_[quantity_vert_ + addition].push_back(second_vert);
    edges_[quantity_vert_ + addition].push_back(first_vert);
    edges_[quantity_vert_ + addition].push_back(third_vert);
    edges_[first_vert].push_back(quantity_vert_ + addition);
    edges_[second_vert].push_back(quantity_vert_ + addition);
    edges_[third_vert].push_back(quantity_vert_ + addition);
  }
  void DFS() {
    for (size_t i = 1; i <= quantity_vert_; ++i) {
      if (colors_[i] == "white") {
        DfsVisit(i, true);
      }
    }
  }
  void DfsVisit(size_t begin_vertex, bool is_root) {
    colors_[begin_vertex] = "gray";
    ++time_;
    time_in_[begin_vertex] = time_;
    time_in_[begin_vertex] = time_;
    for (auto neighbor : edges_[begin_vertex]) {
      if (colors_[neighbor] == "gray") {
        time_up_[begin_vertex] = std::min(time_up_[begin_vertex], time_in_[neighbor]);
      }
      if (colors_[neighbor] == "white") {
        ++n_children_[begin_vertex];
        DfsVisit(neighbor, false);
        time_up_[begin_vertex] = std::min(time_up_[begin_vertex], time_up_[neighbor]);
        if (!is_root && (time_in_[begin_vertex] <= time_up_[neighbor])) {
          if (begin_vertex > quantity_vert_) {
            articulation_points_.insert(begin_vertex);
          }
        }
      }
    }
    if (is_root && (n_children_[begin_vertex] > 1)) {
      if (begin_vertex > quantity_vert_) {
        articulation_points_.insert(begin_vertex);
      }
    }
    colors_[begin_vertex] = "black";
  }
};

int main() {
  size_t quantity_vertexes = 0;
  size_t quantity_edges = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes, quantity_edges * 3);
  size_t first_vert = 0;
  size_t second_vert = 0;
  size_t third_vert = 0;
  for (size_t i = 1; i <= quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert >> third_vert;
    graph.PushEdge(first_vert, second_vert, third_vert, i);
  }
  graph.DFS();
  std::cout << graph.articulation_points_.size() << '\n';
  for (auto it : graph.articulation_points_) {
    std::cout << it - quantity_vertexes << '\n';
  }
}