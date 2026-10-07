#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int64_t from_;
  int64_t to_;
  int64_t weight_;
  Edge(const int64_t& from, const int64_t& to, const int64_t& weight) : from_(from), to_(to), weight_(weight) {
  }
  Edge() = default;
};

bool operator<(const Edge& first, const Edge& second) {
  return ((first.weight_ < second.weight_) || ((first.weight_ == second.weight_) && (first.from_ < second.from_)) ||
          ((first.weight_ == second.weight_) && (first.from_ == second.from_) && (first.to_ < second.to_)));
}

class DSU {
 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;

 public:
  DSU() = default;
  explicit DSU(int64_t quantity_vert) {
    parent_.resize(quantity_vert + 1);
    rank_.resize(quantity_vert + 1);
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
  void Union(int64_t first_vertex, int64_t second_vertex) {
    first_vertex = FindSet(first_vertex);
    second_vertex = FindSet(second_vertex);
    if (first_vertex == second_vertex) {
      return;
    }
    if (rank_[first_vertex] < rank_[second_vertex]) {
      parent_[first_vertex] = second_vertex;
    } else if (rank_[first_vertex] > rank_[second_vertex]) {
      parent_[second_vertex] = first_vertex;
    } else {
      parent_[first_vertex] = second_vertex;
      rank_[second_vertex] += 1;
    }
  }
};
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  std::vector<Edge> edges;
  std::cin >> quantity_vertexes;
  DSU dsu(quantity_vertexes + 1);
  int64_t weight = 0;
  for (int64_t i = 0; i < quantity_vertexes; ++i) {
    for (int64_t j = 0; j < quantity_vertexes; ++j) {
      std::cin >> weight;
      if (i < j) {
        edges.emplace_back(i, j, weight);
      }
    }
  }
  for (int64_t j = 0; j < quantity_vertexes; ++j) {
    std::cin >> weight;
    edges.emplace_back(quantity_vertexes, j, weight);
  }
  std::sort(edges.begin(), edges.end());
  int64_t weight_mst = 0;
  for (auto& edge : edges) {
    if (dsu.FindSet(edge.from_) != dsu.FindSet(edge.to_)) {
      dsu.Union(edge.from_, edge.to_);
      weight_mst += edge.weight_;
    }
  }
  std::cout << weight_mst;
}