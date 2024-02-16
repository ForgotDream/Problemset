#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 3e5 + 50;

int n, fa[N], st[N], dep[N], k;
std::vector<int> adj[N];

void dfs(int u, int frm) {
  fa[u] = frm, st[u] = 0;
  dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
  }
}

void calc(int u, int v, int idx) {
  while (true) {
    if (dep[u] < dep[v]) std::swap(u, v);
    st[u] |= 1 << (idx - 1);
    u = fa[u];
    if (u == v) break;
  }
}

i64 f[1 << 20];

void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) adj[i].clear();
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(1, 0);
  std::cin >> k;
  for (int u, v, i = 1; i <= k; i++) {
    std::cin >> u >> v;
    calc(u, v, i);
  }
  std::set<int> s;
  for (int i = 1; i <= n; i++) s.insert(st[i]);
  int mask = 1 << k;
  std::fill(f + 1, f + mask, 1e9);
  f[0] = 0;
  for (int i = 0; i < mask; i++) {
    for (auto j : s) {
      f[i | j] = std::min(f[i | j], f[i] + 1);
    }
  }
  std::cout << f[mask - 1] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
