#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n;
std::vector<int> adj[N];
int siz[N], ans;
void dfs(int u, int frm) {
  siz[u] = 1;
  int sum = 0, mn = 0;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u), sum += siz[v], mn = std::max(mn, siz[v]);
    siz[u] += siz[v];
  }
  if (u == 1) ans = sum - mn;
}
void solve() {
  std::cin >> n;
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  std::cout << ans + 1 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
