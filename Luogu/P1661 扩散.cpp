/**
 * @file    P1661 扩散.cpp
 * @author  ForgotDream
 * @brief   二分 + DSU
 * @date    2023-03-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Point {
  int x, y;
  Point() : x(0), y(0) {}
};

struct DSU {
  int n;
  std::vector<int> fa;

  DSU(int n) {
    this->n = n;
    fa.resize(n);
    std::iota(fa.begin(), fa.end(), 0);
    return;
  }

  int find(int u) {
    return u == fa[u] ? u : fa[u] = find(fa[u]);
  }

  void merge(int u, int v) {
    int fau = find(u), fav = find(v);
    if (fau == fav) {
      return;
    }
    fa[fau] = fav;
    return;
  }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<Point> a(n);
  for (auto &i : a) {
    std::cin >> i.x >> i.y;
  }

  auto calc = [&](int u, int v) {
    return (std::abs(a[u].x - a[v].x) + std::abs(a[u].y - a[v].y) + 1) / 2;
  };

  int l = 0, r = 1e9;
  while (l <= r) {
    int mid = (l + r) >> 1;
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (calc(i, j) <= mid) {
          dsu.merge(i, j);
        }
      }
    }

    int cnt = 0;
    for (int i = 0; i < n; i++) {
      if (i == dsu.find(i)) {
        cnt++;
      }
    }

    if (cnt == 1) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  std::cout << l << "\n";

  return 0;
}