#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using i64 = long long;
using f80 = long double;
using ti3 = std::tuple<int, int, int>;

constexpr int N = 2e5 + 50;
constexpr f80 eps = 1e-15;
int n, m;
std::vector<ti3> adj[N];
int deg[N], tmp[N];
f80 dis[N];
bool check(f80 mid) {
  std::queue<int> q;
  for (int i = 1; i <= n; i++) dis[i] = -1e18, tmp[i] = deg[i];
  dis[1] = 0;
  for (int i = 1; i <= n; i++) if (!tmp[i]) q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto [v, b, c] : adj[u]) {
      f80 nxt = dis[u] + b - mid * c;
      if (dis[v] + eps < nxt) dis[v] = nxt;
      if (!--tmp[v]) q.push(v);
    }
  }
  return dis[n] < eps;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v, b, c; i <= m; i++) {
    std::cin >> u >> v >> b >> c;
    adj[u].emplace_back(v, b, c), deg[v]++;
  }
  f80 l = 0, r = 1e4;
  while (fabs(r - l) > eps) {
    f80 mid = (l + r) / 2;
    if (check(mid)) r = mid;
    else l = mid;
  }
  std::cout << std::fixed << std::setprecision(12) << (l + r) / 2 << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
