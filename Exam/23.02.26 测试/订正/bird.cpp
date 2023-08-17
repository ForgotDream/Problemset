#include <bits/stdc++.h>

using i64 = long long;

static const int N = 1e5 + 50, INF = 0x3f3f3f3f, M = 4e6 + 50;
struct Bird {
  int x1, y1, x2, y2;
};

void convert(Bird &i) {
  if (i.x1 > i.x2) {
    std::swap(i.x1, i.x2);
  }
  if (i.y1 > i.y2) {
    std::swap(i.y1, i.y2);
  }
  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q, x, y;

  std::cin >> n >> q;
  std::cin >> x >> y;

  std::vector<Bird> bird(n);
  std::vector<int> d(M);

  for (auto &i : bird) {
    std::cin >> i.x1 >> i.y1 >> i.x2 >> i.y2;
    convert(i);
  }

  for (int i = 0; i < n; i++) {
    int x1 = bird[i].x1, x2 = bird[i].x2;
    int y1 = bird[i].y1, y2 = bird[i].y2;

    int maxx = 0, minn = INF;
    int d1 = std::abs(x - x1), d2 = std::abs(x - x2);
    int d3 = std::abs(y - y1), d4 = std::abs(y - y2);

    maxx = std::max(maxx, d1 + d3);
    maxx = std::max(maxx, d2 + d4);
    maxx = std::max(maxx, d1 + d4);
    maxx = std::max(maxx, d2 + d3);

    minn = std::min(minn, d1 + d3);
    minn = std::min(minn, d2 + d4);
    minn = std::min(minn, d1 + d4);
    minn = std::min(minn, d2 + d3);

    if (x >= x1 && x <= x2) {
      if (y >= y1 && y <= y2) {
        minn = 0;
      } else {
        minn = std::min(d3, d4);
      }
    } else if (y >= y1 && y <= y2) {
      minn = std::min(d1, d2);
    }

    d[minn]++;
    d[maxx + 1]--;
  }

  for (int i = 1; i < M; i++) {
    d[i] += d[i - 1];
  }

  for (int i = 1; i <= q; i++) {
    int u;
    std::cin >> u;
    std::cout << d[u] << '\n';
  }

  return 0;
}