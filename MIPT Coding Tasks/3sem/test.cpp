#include <iostream>
#include <vector>

struct Point {
	int64_t x = 0;
	int64_t y = 0;
};

struct Rect {
	Point l;
	Point r;
};

bool Cross(Point l1, Point l2, Point r1, Point r2) {
	bool c = true;
	int64_t ai = (l2.x - l1.x) * (r1.y - l1.y) - (l2.y - l1.y) * (r1.x - l1.x);
	int64_t bi = (l2.x - l1.x) * (r2.y - l1.y) - (l2.y - l1.y) * (r2.x - l1.x);
	bool a = ai >= 0;
	bool b = bi >= 0;
	c = (a != b || (ai == 0 && bi == 0));
	ai = (r2.x - r1.x) * (l1.y - r1.y) - (r2.y - r1.y) * (l1.x - r1.x);
	bi = (r2.x - r1.x) * (l2.y - r1.y) - (r2.y - r1.y) * (l2.x - r1.x);
	a = ai >= 0;
	b = bi >= 0;
	c *= (a != b || (ai == 0 && bi == 0));
	if ((l2.y - l1.y) * (r2.x - r1.x) == (l2.x - l1.x) * (r2.y - r1.y)) {
		c = false;
	}
	return c;
}

bool CrossRect(Rect rec1, Rect rec2) {
  Point r1pup;
  r1pup.x = rec1.l.x;
  r1pup.y = rec1.r.y;
  Point r2pup;
  r2pup.x = rec2.l.x;
  r2pup.y = rec2.r.y;
  Point r1pdown;
  r1pdown.x = rec1.r.x;
  r1pdown.y = rec1.l.y;
  Point r2pdown;
  r2pdown.x = rec2.r.x;
  r2pdown.y = rec2.l.y;
  if (Cross(rec1.l, r1pup, r2pup, rec2.r)) {
    return true;
  }
  if (Cross(rec1.l, r1pup, rec2.l, r2pdown)) {
    return true;
  }
  if (Cross(rec1.r, r1pdown, r2pup, rec2.r)) {
    return true;
  }
  if (Cross(rec1.r, r1pdown, rec2.l, r2pdown)) {
    return true;
  }
  return false;
}

int main() {
	int n = 0;
	std::cin >> n;
	std::vector<Rect> rect(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> rect[i].l.x >> rect[i].l.y >> rect[i].r.x >> rect[i].r.y;
	}
	std::vector<int> ans(n);
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
		    if (CrossRect(rect[i], rect[j])) {
		        ++ans[i];
		        ++ans[j];
		    }
		}
	}
	for (int i = 0; i < n; ++i) {
		std::cout << ans[i] << ' '; 
	}
}