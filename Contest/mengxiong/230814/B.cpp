#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 5e5 + 50;
int n, f[N], son[N], pre[N], siz[N];
std::vector<int> adj[N];
void dfs(int u, int frm) {
  siz[u] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u), son[u]++, siz[u] += siz[v];
  }
  std::sort(adj[u].begin(), adj[u].end(),
            [&](int lhs, int rhs) { return siz[lhs] < siz[rhs]; });
  int cur = 0;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    pre[v] = cur, cur = v;
    f[u] = std::max({f[u], f[v], siz[pre[v]]});
  }
  if (son[u] > 1) f[u] = std::max(f[u], 1);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  std::cout << f[1] << "\n";
  return 0;
}