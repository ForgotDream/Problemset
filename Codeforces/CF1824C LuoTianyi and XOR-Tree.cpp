/**
 * @file    CF1824C LuoTianyi and XOR-Tree.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-11-12
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 2e5 + 50;
int n, a[N];
std::vector<int> adj[N];
std::map<int, int> f[N];
int ans;
void dfs(int u, int frm) {
  int cnt = 0, mx = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    a[v] ^= a[u], dfs(v, u), cnt++;
    if (f[u].size() < f[v].size()) std::swap(f[u], f[v]);
    for (auto [key, val] : f[v]) mx = std::max(mx, f[u][key] += val);
  }
  if (!cnt) return f[u][a[u]] = 1, void();
  ans += cnt - mx;
  std::map<int, int> tmp;
  if (mx > 1) {
    for (auto [key, val] : f[u]) {
      if (val == mx) tmp[key] = 1;
    }
    std::swap(f[u], tmp);
  }
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  std::cout << ans + (!f[1][0]) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
