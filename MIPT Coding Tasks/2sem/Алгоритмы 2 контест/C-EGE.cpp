#include <iostream>
#include <vector>
#include <queue>

class Graph {
 private:
  std::vector<std::vector<size_t> > edges_;
  size_t quantity_vert_ = 9999;

 public:
  size_t begin_vertex_;
  size_t end_vertex_;
  std::vector<size_t> dist_;
  std::vector<size_t> parent_;
  Graph(const size_t new_begin_vertex, const size_t new_end_vertex)
      : begin_vertex_(new_begin_vertex), end_vertex_(new_end_vertex) {
    edges_.resize(quantity_vert_ + 1);
    dist_.resize(quantity_vert_ + 1, 777);
    parent_.resize(quantity_vert_ + 1);
  }
  bool PushEdges(size_t first_vert) {
    bool is_find_num = false;
    if ((first_vert / 1000) != 9) {
      edges_[first_vert].push_back(first_vert + 1000);
      is_find_num = (is_find_num || (first_vert + 1000 == end_vertex_));
    }
    if (first_vert % 10 != 1) {
      edges_[first_vert].push_back(first_vert - 1);
      is_find_num = (is_find_num || (first_vert - 1 == end_vertex_));
    }
    size_t new_num = first_vert / 10 + (first_vert % 10) * 1000;
    edges_[first_vert].push_back(new_num);
    is_find_num = (is_find_num || (new_num == end_vertex_));
    new_num = first_vert % 1000 * 10 + first_vert / 1000;
    edges_[first_vert].push_back(new_num);
    is_find_num = (is_find_num || (new_num == end_vertex_));
    return is_find_num;
  }
  void BFS() {
    std::queue<size_t> queue;
    queue.push(begin_vertex_);
    dist_[begin_vertex_] = 0;
    size_t new_vertex = 0;
    bool is_find = false;
    while (!is_find) {
      new_vertex = queue.front();
      queue.pop();
      is_find = PushEdges(new_vertex);
      for (auto neighbor : edges_[new_vertex]) {
        if (dist_[neighbor] == 777) {
          dist_[neighbor] = dist_[new_vertex] + 1;
          parent_[neighbor] = new_vertex;
          queue.push(neighbor);
        }
      }
    }
  }
};

int main() {
  size_t begin_vertex = 0;
  size_t end_vertex = 0;
  std::cin >> begin_vertex >> end_vertex;
  Graph graph(begin_vertex, end_vertex);
  graph.BFS();
  if (graph.dist_[end_vertex] == 777) {
    std::cout << -1 << '\n';
  } else if (begin_vertex == end_vertex) {
    std::cout << 0 << '\n';
    std::cout << begin_vertex;
  } else {
    std::cout << graph.dist_[end_vertex] << '\n';
    std::vector<size_t> path;
    path.push_back(end_vertex);
    for (size_t i = graph.parent_[end_vertex]; i != begin_vertex; i = graph.parent_[i]) {
      path.push_back(i);
    }
    path.push_back(begin_vertex);
    for (size_t i = path.size() - 1; i > 0; --i) {
      std::cout << path[i] << ' ';
    }
    std::cout << path[0];
  }
}