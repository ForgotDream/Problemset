#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> g(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v;
    std::cin >> u >> v;
    g[u].push_back(v), g[v].push_back(u);
  }

  int s;
  std::cin >> s;

  std::queue<int> q;
  std::vector<bool> vis(n + 1);
  std::vector<int> dis(n + 1);
  q.push(s), vis[s] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      if (vis[v]) {
        continue;
      }
      dis[v] = dis[u] + 1;
      vis[v] = true;
      q.push(v);
    }
  }

  std::cout << *std::max_element(dis.begin(), dis.end()) + 1 << "\n";

  return 0;
}