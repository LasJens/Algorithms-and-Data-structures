#include <functional>
#include <iostream>
#include <set>
#include <vector>

struct Edge {
  int64_t from_;
  int64_t to_;
  int64_t weight_;
  Edge(const int64_t& from, const int64_t& to, const int64_t& weight) : from_(from), to_(to), weight_(weight) {
  }
  Edge() = default;
};

class Graph {
 private:
  std::vector<Edge> edges_;
  int64_t quantity_vert_;
  int64_t quantity_edges_;

 public:
  std::vector<int64_t> dist_;
  explicit Graph(const int64_t& new_quantity_vert, const int64_t& new_quantity_edges)
      : quantity_vert_(new_quantity_vert), quantity_edges_(new_quantity_edges) {
    dist_.resize(quantity_vert_ + 1, 2000000000);
  }
  void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
    edges_.emplace_back(first_vert, second_vert, weight);
  }
  void Bellman() {
    dist_[1] = 0;
    for (int i = 2; i <= quantity_vert_; i++) {
      for (int j = 0; j < quantity_edges_; j++) {
        int64_t u = edges_[j].from_;
        int64_t v = edges_[j].to_;
        int64_t weight = edges_[j].weight_;
        if (dist_[u] != 2000000000 && dist_[u] + weight < dist_[v]) {
          dist_[v] = dist_[u] + weight;
        }
      }
    }
  }
  void Print() {
    for (int i = 1; i <= quantity_vert_; ++i) {
      if (dist_[i] == 2000000000) {
        std::cout << 30000 << " ";
      } else {
        std::cout << dist_[i] << " ";
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes, quantity_edges);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  int64_t weight = 0;
  for (int64_t i = 1; i <= quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert >> weight;
    graph.PushEdge(first_vert, second_vert, weight);
  }
  graph.Bellman();
  graph.Print();
}