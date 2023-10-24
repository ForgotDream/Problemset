#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<std::vector<int>> g(n + 1);
  bool flg = true;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    if (v != u + 1) {
      flg = false;
    }
    g[u].push_back(v), g[v].push_back(u);
  }

  if (flg) {
    std::cout << ((n - k + 1) >> 1) << "\n";
    return 0;
  }

  std::vector<int> dis(n + 1);
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    for (auto v : g[u]) {
      if (v == frm) {
        continue;
      }
      dis[v] = dis[u] + 1;
      dfs(v, u);
    }
  };

  int l = 0;
  dfs(1, 0);
  for (int i = 0; i < n; i++) {
    if (dis[i] > dis[l]) {
      l = i;
    }
  }
  dfs(l, 0);

  std::cout << (*max_element(dis.begin(), dis.end()) / 2) << "\n";

  return 0;
}