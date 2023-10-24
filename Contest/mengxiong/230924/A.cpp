#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using i64 = long long;

constexpr int N = 1e5 + 50;
int n, m, a[N], p[N];
std::vector<int> adj[N];
bool vis[N];
struct DSU {
  int fa[N], rnk[N];
  i64 sum[N];
  std::multiset<i64> s;
  DSU() { std::iota(fa, fa + N, 0), std::fill(rnk, rnk + N, 1); }
  int find(int u) { return u == fa[u] ? u : find(fa[u]); }
  void setVal(int u, int val) { sum[u] = val; }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (rnk[u] > rnk[v]) std::swap(u, v);
    if (s.count(sum[v])) s.erase(s.find(sum[v]));
    if (s.count(sum[u])) s.erase(s.find(sum[u]));
    sum[v] += sum[u], fa[u] = v;
    if (rnk[u] == rnk[v]) rnk[v]++;
    s.insert(sum[v]);
    return true;
  }
  i64 query() { return s.empty() ? 0 : *s.rbegin(); }
} dsu;
i64 ans[N];
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i], dsu.setVal(i, a[i]);
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) std::cin >> p[i];
  for (int i = n; i; i--) {
    ans[i] = dsu.query();
    int u = p[i];
    dsu.s.insert(a[u]);
    for (auto v : adj[u]) {
      if (!vis[v]) continue;
      dsu.merge(u, v);
    }
    vis[u] = true;
  }
  for (int i = 1; i <= n; i++) std::cout << ans[i] << "\n";
}

int main() {
  std::freopen("qd.in", "r", stdin);
  std::freopen("qd.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
