/**
 * @file    CF1406C Link Cut Centroids.cpp
 * @author  ForgotDream
 * @brief   Tree Centroids
 * @date    2023-05-09
 */
#include <bits/stdc++.h>

using i64 = long long;

void solve() {
  int n;
  std::cin >> n;

  std::vector g(n + 1, std::vector<int>());
  int l, r;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    if (i == 0) {
      l = u, r = v;
    }
    g[u].push_back(v), g[v].push_back(u);
  }

  if (n & 1) {
    std::cout << l << " " << r << "\n";
    std::cout << l << " " << r << "\n";
    return;
  }

  std::vector<int> siz(n + 1), maxsiz(n + 1), ctr;
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    siz[u] = 1, maxsiz[u] = 0;
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
    return;
  };

  dfs(1, 0);

  if (ctr.size() == 1) {
    std::cout << l << " " << r << "\n";
    std::cout << l << " " << r << "\n";
    return;
  }

  int pivot;
  for (auto v : g[ctr[0]]) {
    if (v != ctr[1]) {
      pivot = v;
      break;
    }
  }

  std::cout << ctr[0] << " " << pivot << "\n";
  std::cout << ctr[1] << " " << pivot << "\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}