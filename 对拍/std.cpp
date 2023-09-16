#include <iostream>
#include <queue>
#include <vector>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, d;
std::vector<int> adj[N];
std::queue<int> q;
int deg[N];
bool vis[N];
void solve() {
  std::cin >> n >> m >> d;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(u), adj[v].push_back(u);
    deg[u]++, deg[v]++;
  }
  for (int i = 1; i <= n; i++) {
    if (deg[i] < d) q.push(i);
  }
  int ans = n;
  while (!q.empty()) {
    int u = q.front();
    q.pop(), vis[u] = true, ans--;
    for (auto v : adj[u]) {
      if (!vis[v] && --deg[v] < d) q.push(v);
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}