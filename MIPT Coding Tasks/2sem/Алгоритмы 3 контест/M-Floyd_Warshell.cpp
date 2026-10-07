#include <iostream>
#include <vector>
#include <queue>

class Graph {
 private:
  int64_t quantity_vert_;

 public:
  std::vector<std::vector<int64_t> > dist_matrix_;
  Graph() = default;
  explicit Graph(const int64_t& new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    dist_matrix_.resize(quantity_vert_);
    for (int64_t i = 0; i < quantity_vert_; ++i) {
      dist_matrix_[i].resize(quantity_vert_, 30000000);
    }
  }
  void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
    dist_matrix_[first_vert][second_vert] = weight;
  }
  void FloydWarshall() {
    for (int64_t cur = 0; cur < quantity_vert_; ++cur) {
      for (int64_t first_vertex = 0; first_vertex < quantity_vert_; ++first_vertex) {
        for (int64_t second_vertex = 0; second_vertex < quantity_vert_; ++second_vertex) {
          dist_matrix_[first_vertex][second_vertex] =
              std::min(dist_matrix_[first_vertex][second_vertex],
                       dist_matrix_[first_vertex][cur] + dist_matrix_[cur][second_vertex]);
        }
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  std::cin >> quantity_vertexes;
  Graph graph(quantity_vertexes);
  int64_t weight = 0;
  for (int64_t i = 0; i < quantity_vertexes; ++i) {
    for (int64_t j = 0; j < quantity_vertexes; ++j) {
      std::cin >> weight;
      graph.PushEdge(i, j, weight);
    }
  }
  graph.FloydWarshall();
  for (int64_t i = 0; i < quantity_vertexes; ++i) {
    for (int64_t j = 0; j < quantity_vertexes; ++j) {
      std::cout << graph.dist_matrix_[i][j] << ' ';
    }
    std::cout << '\n';
  }
}