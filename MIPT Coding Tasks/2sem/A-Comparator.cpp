#include <iostream>
#include <algorithm>
#include <vector>

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
  std::vector<Team> teams;
  for (int i = 0; i < n; ++i) {
    Team cur;
    std::cin >> cur.score;
    std::cin >> cur.time;
    cur.num = i + 1;
    teams.push_back(cur);
  }
  std::sort(teams.begin(), teams.end(), Compare());
  for (int i = 0; i < n; ++i) {
    std::cout << teams[i].num << '\n';
  }
}