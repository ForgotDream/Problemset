/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using seg = std::pair<int, int>;

void solve() {
  int n;
  std::cin >> n;
  std::vector<seg> a(n);
  for (int i = 0; i < n; i++) { std::cin >> a[i].first >> a[i].second; }
  std::sort(a.begin(), a.end());
  std::vector<std::vector<int>> adj(n);
  std::vector<int> deg(n);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[j].first <= a[i].second) {
        adj[i].push_back(j), deg[j]++;
      } else {
        break;
      }
    }
  }
  int ans = 0;
  std::vector f(n, std::vector<int>(3));
  std::function<void(int)> dfs = [&](int u) {
    if (!adj[u].size()) {
      f[u][1] = 1;
      return;
    }
    for (auto v : adj[u]) {
      dfs(v);
      f[u][0] = std::max({f[u][0], f[v][0], f[v][1], f[v][2]});
      f[u][1] = std::max({f[u][1], f[v][0], f[v][2]});
      f[u][2] = std::max({f[u][2], f[v][0]});
    }
  };
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) { solve(); }

  return 0;
}