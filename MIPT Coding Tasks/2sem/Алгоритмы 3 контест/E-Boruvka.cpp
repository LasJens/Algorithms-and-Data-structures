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

class DSU {
 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;

 public:
  int64_t quantity_trees_;
  DSU() = default;
  explicit DSU(int64_t quantity_vert) : quantity_trees_(quantity_vert) {
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
  bool Union(int64_t first_vertex, int64_t second_vertex) {
    first_vertex = FindSet(first_vertex);
    second_vertex = FindSet(second_vertex);
    if (first_vertex == second_vertex) {
      return false;
    }
    if (rank_[first_vertex] < rank_[second_vertex]) {
      parent_[first_vertex] = second_vertex;
    } else if (rank_[first_vertex] > rank_[second_vertex]) {
      parent_[second_vertex] = first_vertex;
    } else {
      parent_[first_vertex] = second_vertex;
      rank_[second_vertex] += 1;
    }
    --quantity_trees_;
    return true;
  }
};
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  std::vector<Edge> edges;
  std::cin >> quantity_vertexes >> quantity_edges;
  DSU dsu(quantity_vertexes);
  int64_t first_vert = 0;
  int64_t second_vert = 0;
  int64_t weight = 0;
  for (int64_t i = 1; i <= quantity_edges; ++i) {
    std::cin >> first_vert >> second_vert >> weight;
    edges.emplace_back(first_vert, second_vert, weight);
  }
  int64_t weight_mst = 0;
  while (dsu.quantity_trees_ > 1) {
    std::vector<Edge> min_edge;
    min_edge.resize(quantity_vertexes, Edge(-1, -1, 2000000000));
    for (auto& edge : edges) {
      int64_t component_from = dsu.FindSet(edge.from_);
      int64_t component_to = dsu.FindSet(edge.to_);
      if (component_from != component_to) {
        if (edge.weight_ < min_edge[component_to].weight_) {
          min_edge[component_to] = edge;
        }
        if (edge.weight_ < min_edge[component_from].weight_) {
          min_edge[component_from] = edge;
        }
      }
    }
    for (auto& edge : min_edge) {
      if (edge.from_ == -1) {
        continue;
      }
      if (dsu.Union(edge.from_, edge.to_)) {
        weight_mst += edge.weight_;
      }
    }
  }
  std::cout << weight_mst;
}