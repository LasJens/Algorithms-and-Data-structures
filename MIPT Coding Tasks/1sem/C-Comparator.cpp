#include <iostream>
#include <algorithm>

struct Team {
  int num = 0;
  int score = 0;
  int time = 0;
};

struct Compare {
  bool operator()(Team res1, Team res2) const {
    if (res1.score == res2.score) {
      if (res1.time == res2.time) {
        return res1.num < res2.num;
      }
      return res1.time < res2.time;
    }
    return res1.score > res2.score;
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  auto teams = new Team[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> teams[i].score;
    std::cin >> teams[i].time;
    teams[i].num = i + 1;
  }
  std::sort(teams, teams + n, Compare());
  for (int i = 0; i < n; ++i) {
    std::cout << teams[i].num << '\n';
  }
  delete[] teams;
}