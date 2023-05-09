#include <bits/stdc++.h>

using i64 = long long;

constexpr int MOD = 1e9 + 7;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int n, k;
  std::cin >> n >> k;

  std::vector e(n + 1, std::vector<int>());
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  if (k == 1) {
    std::cout << 1 << "\n";
    return 0;
  }

  std::vector<int> dep(n + 1);
  i64 all = 0, cnt = 0;
  std::function<void(int, int)> dfs = [&](int u, int frm) {
    dep[u] = dep[frm] + 1;
    for (auto v : e[u]) {
      if (v == frm) {
        continue;
      }
      dfs(v, u);
    }
    for (int i = 0; i < e[u].size(); i++) {
      if (k == 2) {
        
      } else {

      }
    }
    return;
  };

  dfs(1, 0);

  return 0;
}