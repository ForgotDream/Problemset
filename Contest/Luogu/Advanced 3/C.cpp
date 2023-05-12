#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<std::vector<int>> g(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }

  std::vector<int> siz(n + 1), maxsiz(n + 1), ctr;
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    siz[u] = 1;
    for (auto v : g[u]) {
      if (v == frm) {
        continue;
      }
      dfs(v, u);
      siz[u] += siz[v];
      maxsiz[u] = std::max(maxsiz[u], siz[v]);
    }
    maxsiz[u] = std::max(maxsiz[u], n - siz[u]);
    if (maxsiz[u] <= n / 2) {
      ctr.push_back(u);
    }
  };

  dfs(1, 0);

  return 0;
}