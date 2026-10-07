#include <algorithm>
#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;

 public:
  DSU() = default;
  int64_t graph_quantity_vertexes;
  std::vector<int64_t> weight_;
  explicit DSU(int64_t quantity_vert) : graph_quantity_vertexes(quantity_vert) {
    parent_.resize(quantity_vert + 1);
    rank_.resize(quantity_vert + 1);
    weight_.resize(quantity_vert + 1, 0);
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
  void Union(int64_t first_vertex, int64_t second_vertex, int64_t weight) {
    first_vertex = FindSet(first_vertex);
    second_vertex = FindSet(second_vertex);
    if (first_vertex == second_vertex) {
      weight_[first_vertex] += weight;
      return;
    }
    if (rank_[first_vertex] < rank_[second_vertex]) {
      parent_[first_vertex] = second_vertex;
      weight_[second_vertex] += weight + weight_[first_vertex];
    } else if (rank_[first_vertex] > rank_[second_vertex]) {
      parent_[second_vertex] = first_vertex;
      weight_[first_vertex] += weight + weight_[second_vertex];
    } else {
      parent_[first_vertex] = second_vertex;
      weight_[second_vertex] += weight + weight_[first_vertex];
      rank_[second_vertex] += 1;
    }
  }
};
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_requests = 0;
  std::cin >> quantity_vertexes >> quantity_requests;
  DSU dsu(quantity_vertexes);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  int64_t operation = 0;
  int64_t weight = 0;
  for (int64_t i = 0; i < quantity_requests; ++i) {
    std::cin >> operation;
    if (operation == 1) {
      std::cin >> first_vert >> second_vert >> weight;
      dsu.Union(first_vert, second_vert, weight);
    } else {
      std::cin >> first_vert;
      int64_t root = dsu.FindSet(first_vert);
      std::cout << dsu.weight_[root] << '\n';
    }
  }
}