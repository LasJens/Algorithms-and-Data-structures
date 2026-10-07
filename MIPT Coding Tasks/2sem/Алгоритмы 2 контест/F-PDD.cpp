#include <iostream>
#include <vector>
#include <queue>

struct Node {
  size_t vert;
  size_t cost;
  Node(size_t new_vert, size_t new_cost) : vert(new_vert), cost(new_cost) {
  }
};

class Graph {
 private:
  std::vector<std::vector<Node> > edges_;
  size_t quantity_vert_;

 public:
  std::vector<size_t> dist_;
  explicit Graph(const size_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
    edges_.resize(quantity_vert_ + 1);
    dist_.resize(quantity_vert_ + 1, 777);
  }
  void PushEdge(size_t first_vert, size_t second_vert) {
    edges_[first_vert].emplace_back(second_vert, 0);
    edges_[second_vert].emplace_back(first_vert, 1);
  }
  void BFS(size_t begin_vertex) {
    std::queue<size_t> queue;
    queue.push(begin_vertex);
    dist_[begin_vertex] = 0;
    size_t new_vertex = 0;
    while (!queue.empty()) {
      new_vertex = queue.front();
      queue.pop();
      for (auto neighbor : edges_[new_vertex]) {
        if ((dist_[neighbor.vert] == 777) || (dist_[neighbor.vert] > dist_[new_vertex] + neighbor.cost)) {
          dist_[neighbor.vert] = dist_[new_vertex] + neighbor.cost;
          queue.push(neighbor.vert);
        }
      }
    }
  }
};

int main() {
  size_t quantity_edges = 0;
  size_t quantity_vertexes = 0;
  size_t begin_vertex = 0;
  size_t end_vertex = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes);
  size_t first_vert = 0;
  size_t second_vert = 0;
  for (size_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert;
    graph.PushEdge(first_vert, second_vert);
  }
  size_t quantity_requests = 0;
  std::cin >> quantity_requests;
  for (size_t i = 0; i < quantity_requests; ++i) {
    std::cin >> begin_vertex >> end_vertex;
    for (size_t i = 1; i <= quantity_vertexes; ++i) {
      graph.dist_[i] = 777;
    }
    graph.BFS(begin_vertex);
    if (graph.dist_[end_vertex] == 777) {
      std::cout << -1 << '\n';
    } else if (begin_vertex == end_vertex) {
      std::cout << 0 << '\n';
    } else {
      std::cout << graph.dist_[end_vertex] << '\n';
    }
  }
}