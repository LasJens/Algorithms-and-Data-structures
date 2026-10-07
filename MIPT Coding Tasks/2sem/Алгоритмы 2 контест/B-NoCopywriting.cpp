#include <iostream>
#include <vector>
#include <queue>

class Graph {
 private:
  std::vector<std::vector<int64_t>> edges_;
  int64_t quantity_vert_;

 public:
  std::vector<int64_t> color_;
  std::vector<int64_t> parent_;
  explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    edges_.resize(quantity_vert_ + 1);
    color_.resize(quantity_vert_ + 1, -1);
    parent_.resize(quantity_vert_ + 1);
  }
  void PushEdge(int64_t first_vert, int64_t second_vert) {
    edges_[first_vert].push_back(second_vert);
    edges_[second_vert].push_back(first_vert);
  }
  bool PaintBFS(int64_t begin_vertex) {
    std::queue<int64_t> queue;
    queue.push(begin_vertex);
    color_[begin_vertex] = 0;
    int64_t new_vertex = 0;
    while (!queue.empty()) {
      new_vertex = queue.front();
      queue.pop();
      for (auto neighbor : edges_[new_vertex]) {
        if (color_[neighbor] == -1) {
          color_[neighbor] = (color_[new_vertex] + 1) % 2;
          parent_[neighbor] = new_vertex;
          queue.push(neighbor);
        } else if ((color_[neighbor] != -1) && (color_[neighbor] == color_[new_vertex])) {
          return false;
        }
      }
    }
    return true;
  }
};

int main() {
  int64_t quantity_edges = 0;
  int64_t quantity_vertexes = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  for (int64_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert;
    graph.PushEdge(first_vert, second_vert);
  }
  bool flag = true;
  for (int64_t i = 1; i <= quantity_vertexes; ++i) {
    if (graph.color_[i] == -1) {
      if (!graph.PaintBFS(i)) {
        std::cout << "NO";
        flag = false;
        break;
      }
    }
  }
  if (flag) {
    std::cout << "YES";
  }
}