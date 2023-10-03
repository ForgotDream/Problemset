#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 5e4 + 50, mod = 2019;
int n, q, c[N];
std::vector<int> adj[N];
int fa[N], siz[N], dep[N];
void dfs(int u, int frm) {
  fa[u] = frm, siz[u] = 1, dep[u] = dep[frm] + 1;
  for (auto v : adj[u]) {
    dfs(v, u);
    siz[u] += siz[v];
  }
}
i64 calc(int u, int rt) {
  i64 res = 0;
  for (auto v : adj[u]) {
    (res += calc(v, rt)) %= mod;
    (res += 1ll * siz[v] * (siz[rt] - siz[v]) % mod * c[v] % mod) %= mod;
  }
  return res;
}
void modify(int u, int v, int w) {
  if (dep[u] < dep[v]) std::swap(u, v);
  while (dep[u] > dep[v]) c[u] = (c[u] + w) % mod, u = fa[u];
  while (u != v) (c[u] += w) %= mod, (c[v] += w) %= mod, u = fa[u], v = fa[v];
}
void solve() {
  std::cin >> n >> q;
  for (int i = 2, p; i <= n; i++) {
    std::cin >> p >> c[i];
    adj[p].push_back(i);
  }
  dfs(1, 0);
  while (q--) {
    char opt[5];
    int u, v, w;
    std::cin >> opt;
    if (opt[0] == 'I') std::cin >> u >> v >> w, modify(u, v, w);
    else std::cin >> u, std::cout << calc(u, u) << "\n";
  }
}

int main() {
  std::freopen("network.in", "r", stdin);
  std::freopen("network.out", "w", stdout);
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
