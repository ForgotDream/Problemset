#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, a[N];
std::vector<int> adj[N], g[N];
int deg[N], f[N];

bool vis[N];
int cnt, bln[N];
void dfs(int u) {
  vis[u] = true, bln[u] = cnt;
  for (auto v : adj[u]) {
    if (vis[v]) continue;
    if (a[u] == a[v]) dfs(v);
  }
}
void dfs2(int u) {
  vis[u] = true;
  for (auto v : adj[u]) {
    if (a[u] == a[v] && !vis[v]) dfs2(v);
    else if (a[u] < a[v]) g[bln[u]].push_back(bln[v]);
  }
}

void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    cnt++, dfs(i);
  }
  for (int i = 1; i <= n; i++) vis[i] = false;
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    dfs2(i);
  }

  for (int i = 1; i <= n; i++) {
    std::sort(g[i].begin(), g[i].end());
    g[i].erase(std::unique(g[i].begin(), g[i].end()), g[i].end());

    for (auto v : g[i]) deg[v]++;
  }

  std::queue<int> q;
  memset(f, -0x3f, sizeof(f)), f[bln[1]] = 1;
  for (int i = 1; i <= cnt; i++) {
    if (deg[i] == 0) q.push(i);
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto v : g[u]) {
      f[v] = std::max(f[v], f[u] + 1);
      if (!--deg[v]) q.push(v);
    }
  }
  if (f[bln[n]] < 0) std::cout << 0 << "\n";
  else std::cout << f[bln[n]] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
