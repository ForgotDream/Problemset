#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1e18;

struct avicii {
  int u, v;
  i64 y;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<avicii> a(m);
  std::vector<i64> lim(n + 1, inf);
  bool flg = false;
  i64 min = inf;
  for (int i = 0; i < m; i++) {
    std::cin >> a[i].u >> a[i].v >> a[i].y;
    lim[a[i].v] = std::min(lim[a[i].v], a[i].y);
    lim[a[i].u] = std::min(lim[a[i].u], a[i].y);
    if (a[i].v == n || a[i].u == n) {
      min = std::min(min, a[i].y);
      flg = true;
    }
  }

  if (m == 0) {
    std::cout << "inf\n";
    return 0;
  } else if (!flg) {
    std::cout << "inf\n";
    return 0;
  }
  for (int i = 1; i < n; i++) {
    if (lim[1] == inf && lim[i] == inf) {
      std::cout << "inf\n";
      return 0;
    }
  }

  std::function<void(int, int, int)> dfs = [&](int u, int cur, int all) {
    if (cur == all) {

      return;
    }
    for (int i = u + 1; i <= n; i++) {
      
    }
  };

  return 0;
}