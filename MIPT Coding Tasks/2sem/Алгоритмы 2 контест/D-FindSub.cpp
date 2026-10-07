#include <iostream>
#include <vector>
#include <queue>

struct Coordinates {
  size_t x_;
  size_t y_;
  Coordinates() = default;
  Coordinates(size_t coord_x, size_t coord_y) : x_(coord_x), y_(coord_y) {
  }
  friend bool operator==(const Coordinates& first, const Coordinates& second) {
    return ((first.x_ == second.x_) && (first.y_ == second.y_));
  }
};

class Graph {
 private:
  std::vector<Coordinates> edge_;
  size_t first_size_;
  size_t second_size_;
  size_t cout_crossroad_;
  size_t size_;
  std::vector<Coordinates> array_crossroad_;

 public:
  std::vector<std::vector<size_t> > dist_;
  Graph(const size_t& n, const size_t& m) : first_size_(n), second_size_(m), size_(n * m) {
    size_t new_crossroad = 0;
    for (size_t i = 0; i < first_size_; ++i) {
      for (size_t j = 0; j < second_size_; ++j) {
        std::cin >> new_crossroad;
        if (new_crossroad) {
          array_crossroad_.emplace_back(i + 1, j + 1);
        }
      }
    }
    cout_crossroad_ = array_crossroad_.size();
    dist_.resize(first_size_ + 1);
    for (size_t i = 0; i < first_size_ + 1; ++i) {
      dist_[i].resize(second_size_ + 1, 777);
    }
  }
  void NewCoordinates(const Coordinates& first_coordinates, const size_t& first_shift, const size_t& second_shift) {
    Coordinates new_coordinates(first_coordinates.x_ + first_shift, first_coordinates.y_ + second_shift);
    if ((new_coordinates.x_ > 0) && (new_coordinates.y_ > 0) && (new_coordinates.x_ < first_size_ + 1) &&
        (new_coordinates.y_ < second_size_ + 1)) {
      edge_.emplace_back(first_coordinates.x_ + first_shift, first_coordinates.y_ + second_shift);
    }
  }
  void PushEdge(const Coordinates& coordinates) {
    NewCoordinates(coordinates, 0, 1);
    NewCoordinates(coordinates, 0, -1);
    NewCoordinates(coordinates, 1, 0);
    NewCoordinates(coordinates, -1, 0);
  }
  void BFS() {
    std::queue<Coordinates> queue;
    size_t array_size = array_crossroad_.size();
    for (size_t i = 0; i < array_size; ++i) {
      queue.push(array_crossroad_[i]);
      dist_[array_crossroad_[i].x_][array_crossroad_[i].y_] = 0;
    }
    Coordinates new_vertex;
    while (cout_crossroad_ != size_) {
      new_vertex = queue.front();
      queue.pop();
      PushEdge(new_vertex);
      for (auto neighbor : edge_) {
        if (dist_[neighbor.x_][neighbor.y_] == 777) {
          dist_[neighbor.x_][neighbor.y_] = dist_[new_vertex.x_][new_vertex.y_] + 1;
          ++cout_crossroad_;
          queue.push(neighbor);
        }
      }
      edge_.resize(0);
    }
  }
};

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  graph.BFS();
  for (size_t i = 1; i < n + 1; ++i) {
    for (size_t j = 1; j < m + 1; ++j) {
      std::cout << graph.dist_[i][j] << ' ';
    }
    std::cout << '\n';
  }
}