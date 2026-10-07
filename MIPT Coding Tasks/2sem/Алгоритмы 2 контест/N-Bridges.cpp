#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int64_t from;
  int64_t to;
  int64_t index;
  Edge(int64_t first, int64_t second, int64_t index) : from(first), to(second), index(index) {
  }
};

bool operator<(const Edge& first, const Edge& second) {
  return first.from < second.from || (first.from == second.from && first.to < second.to);
}

bool operator==(const Edge& first, const Edge& second) {
  return first.from == second.from && first.to == second.to;
}

struct Node {
  int64_t num = 0;
  int64_t time_up = -1;
  int64_t time_in = -1;
  std::vector<Edge> neighbours;
};

class Graph {
 public:
  int64_t time = 0;
  std::vector<Node> nodes_;
  std::vector<int64_t> bridges_;
  Graph(std::vector<Edge> edges, int64_t new_quantity_vert) {
    nodes_ = std::vector<Node>(new_quantity_vert);
    for (int64_t i = 0; i < new_quantity_vert; ++i) {
      nodes_[i].num = i;
    }
    for (auto edge : edges) {
      nodes_[edge.from].neighbours.emplace_back(edge.from, edge.to, edge.index);
      nodes_[edge.to].neighbours.emplace_back(edge.to, edge.from, edge.index);
    }
  }

  void DfsVisit(Edge& edge) {
    int64_t parent = edge.from;
    int64_t son = edge.to;
    nodes_[son].time_in = time;
    nodes_[son].time_up = time;
    time++;
    for (Edge& son_edge : nodes_[son].neighbours) {
      if (son_edge.to == parent) {
        continue;
      }
      if (nodes_[son_edge.to].time_in == -1) {
        DfsVisit(son_edge);
        nodes_[son].time_up = std::min(nodes_[son].time_up, nodes_[son_edge.to].time_up);
      } else {
        nodes_[son].time_up = std::min(nodes_[son].time_up, nodes_[son_edge.to].time_in);
      }
    }
    if (nodes_[son].time_up == nodes_[son].time_in && edge.index != -1) {
      bridges_.emplace_back(edge.index);
    }
  }

  void DFS() {
    for (Node& vertex : nodes_) {
      if (vertex.time_in == -1) {
        vertex.time_in = time;
        vertex.time_up = time;
        time++;
        for (Edge& edge : vertex.neighbours) {
          if (nodes_[edge.to].time_in == -1) {
            DfsVisit(edge);
          }
        }
      }
    }
    std::sort(bridges_.begin(), bridges_.end());
  }
};

int main() {
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  std::vector<Edge> edges;
  int64_t from = 0;
  int64_t to = 0;
  for (int64_t i = 1; i <= quantity_edges; ++i) {
    std::cin >> from >> to;
    edges.emplace_back(std::min(from, to) - 1, std::max(from, to) - 1, i);
  }
  std::sort(edges.begin(), edges.end());
  for (size_t i = 1; i < edges.size(); ++i) {
    if (edges[i] == edges[i - 1]) {
      edges[i].index = -1;
      edges[i - 1].index = -1;
    }
  }
  Graph graph(edges, quantity_vertexes);
  graph.DFS();
  std::cout << graph.bridges_.size() << '\n';
  for (size_t i = 0; i < graph.bridges_.size(); ++i) {
    std::cout << graph.bridges_[i] << " ";
  }
}