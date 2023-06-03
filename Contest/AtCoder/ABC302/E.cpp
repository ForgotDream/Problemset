#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;

  std::vector<bool> conn(n, false);
  std::vector<std::set<int>> g(n);
  int cnt = n;
  while (q--) {
    int opt;
    std::cin >> opt;

    if (opt == 1) {
      int u, v;
      std::cin >> u >> v;
      u--, v--;
      if (g[u].empty()) {
        cnt--;
      }
      if (g[v].empty()) {
        cnt--;
      }
      g[u].insert(v), g[v].insert(u);
      std::cout << cnt << "\n";
    } else {
      int u;
      std::cin >> u;
      u--;
      if (g[u].empty()) {
        std::cout << cnt << "\n";
        continue;
      }
      cnt++;
      for (auto v : g[u]) {
        g[v].erase(u);
        if (g[v].empty()) {
          cnt++;
        }
      }
      g[u].clear();
      std::cout << cnt << "\n";
    }
  }

  return 0;
}