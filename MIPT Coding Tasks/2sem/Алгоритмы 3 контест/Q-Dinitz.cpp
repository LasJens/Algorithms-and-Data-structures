#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int64_t vert;
  int64_t flow;
  int64_t capacity;
  Edge(int64_t vum, int64_t capum) : vert(vum), flow(0), capacity(capum) {
  }
};

class Graph {
 public:
  std::vector<Edge> edges_;
  std::vector<std::vector<int64_t>> vert_;
  std::vector<int64_t> tin_;
  std::vector<int64_t> ptr_;
  std::queue<int64_t> queue_;
  int64_t timer_ = 1;
  int64_t cur_ = 0;
  Graph(int64_t num, int64_t m) : vert_(num), tin_(num), ptr_(num), cur_(num) {
    int64_t temp1 = 0;
    int64_t temp2 = 0;
    int64_t temp3 = 0;
    for (int64_t i = 0; i < m; ++i) {
      std::cin >> temp1 >> temp2 >> temp3;
      vert_[temp1 - 1].push_back(static_cast<int64_t>(edges_.size()));
      edges_.emplace_back(temp2 - 1, temp3);
      vert_[temp2 - 1].push_back(static_cast<int64_t>(edges_.size()));
      edges_.emplace_back(temp1 - 1, 0);
    }
  }
  int64_t DFSFlow(int64_t vert, int64_t flow) {
    if (flow == 0) {
      return 0;
    }
    if (vert == (cur_ - 1)) {
      return flow;
    }
    for (; ptr_[vert] < static_cast<int64_t>(vert_[vert].size()); ++ptr_[vert]) {
      int64_t id = vert_[vert][ptr_[vert]];
      int64_t to = edges_[id].vert;
      if ((tin_[to] != tin_[vert] + 1) || ((edges_[id].capacity - edges_[id].flow) < 1)) {
        continue;
      }
      int64_t pushed = DFSFlow(to, std::min(flow, edges_[id].capacity - edges_[id].flow));
      if (pushed != 0) {
        edges_[id].flow += pushed;
        edges_[id ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }
  bool BFSFlow() {
    while (!queue_.empty()) {
      int64_t vert = queue_.front();
      queue_.pop();
      for (int64_t id : vert_[vert]) {
        if (edges_[id].capacity - edges_[id].flow < 1) {
          continue;
        }
        if (tin_[edges_[id].vert] != -1) {
          continue;
        }
        tin_[edges_[id].vert] = tin_[vert] + 1;
        queue_.push(edges_[id].vert);
      }
    }
    return (tin_[cur_ - 1] != -1);
  }
  int64_t Dinitz() {
    int64_t max_flow = 0;
    while (true) {
      std::fill(tin_.begin(), tin_.end(), -1);
      tin_[0] = 0;
      queue_.push(0);
      if (!BFSFlow()) {
        break;
      }
      std::fill(ptr_.begin(), ptr_.end(), 0);
      while (int64_t pushed = DFSFlow(0, INT_MAX)) {
        max_flow += pushed;
      }
    }
    return max_flow;
  }
};

int main() {
  int64_t quantity_vertexes = 0;
  int64_t quantity_edges = 0;
  std::cin >> quantity_vertexes >> quantity_edges;
  Graph graph(quantity_vertexes, quantity_edges);
  std::cout << graph.Dinitz();
}