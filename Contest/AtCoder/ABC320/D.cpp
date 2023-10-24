#include <iostream>
#include <tuple>
#include <vector>

using i64 = long long;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 2e5 + 50;
int n, m;
std::vector<ti3> adj[N];
bool vis[N];
i64 cx[N], cy[N];
void dfs(int u) {
  vis[u] = true;
  for (auto [v, x, y] : adj[u]) {
    if (vis[v]) continue;
    cx[v] = cx[u] + x, cy[v] = cy[u] + y;
    dfs(v);
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, x, y; i <= m; i++) {
    std::cin >> u >> v >> x >> y;
    adj[u].emplace_back(v, x, y);
    adj[v].emplace_back(u, -x, -y);
  }
  dfs(1);
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) std::cout << "undecidable\n";
    else std::cout << cx[i] << " " << cy[i] << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}