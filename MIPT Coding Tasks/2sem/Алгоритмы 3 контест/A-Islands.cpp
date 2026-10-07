#include <algorithm>
#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;
 public:
  DSU() = default;
  std::vector<int64_t> quantity_vertex_;
  int64_t graph_quantity_vertexes;
  explicit DSU(int64_t quantity_vert) : graph_quantity_vertexes(quantity_vert) {
    parent_.resize(quantity_vert + 1);
    rank_.resize(quantity_vert + 1);
    quantity_vertex_.resize(quantity_vert + 1, 1);
    for (int64_t i = 0; i < quantity_vert; ++i) {
      MakeSet(i);
    }
  }
  void MakeSet(int64_t vertex) {
    parent_[vertex] = vertex;
    rank_[vertex] = 1;
  }
  int64_t FindSet(int64_t vertex) {
    if (vertex == parent_[vertex]) {
      return vertex;
    }
    return parent_[vertex] = FindSet((parent_[vertex]));
  }
  bool Union(int64_t first_vertex, int64_t second_vertex) {
    first_vertex = FindSet(first_vertex);
    second_vertex = FindSet(second_vertex);
    if (first_vertex == second_vertex) {
      return false;
    }
    if (rank_[first_vertex] < rank_[second_vertex]) {
      parent_[first_vertex] = second_vertex;
      quantity_vertex_[second_vertex] += quantity_vertex_[first_vertex];
    } else if (rank_[first_vertex] > rank_[second_vertex]) {
      parent_[second_vertex] = first_vertex;
      quantity_vertex_[first_vertex] += quantity_vertex_[second_vertex];
    } else {
      parent_[first_vertex] = second_vertex;
      quantity_vertex_[second_vertex] += quantity_vertex_[first_vertex];
      rank_[second_vertex] += 1;
    }
    return ((quantity_vertex_[first_vertex] == graph_quantity_vertexes) ||
            (quantity_vertex_[second_vertex] == graph_quantity_vertexes));
  }
};

int main() {
  int64_t quantity_edges = 0;
  int64_t quantity_vertexes = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  DSU dsu(quantity_vertexes);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  for (int64_t i = 0; i < quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert;
    if (dsu.Union(first_vert, second_vert)) {
      std::cout << i + 1;
      break;
    };
  }
}