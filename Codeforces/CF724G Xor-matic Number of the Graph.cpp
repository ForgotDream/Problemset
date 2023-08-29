/**
 * @file    CF724G Xor-matic Number of the Graph.cpp
 * @author  ForgotDream
 * @brief   Linear Basis
 * @date    2023-08-28
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;
using u64 = unsigned long long;
using pil = std::pair<int, i64>;

namespace VECSPACE {
constexpr int N = 64;
struct LinearBasis {
  u64 p[N];
  int cnt;
  LinearBasis() { init(); }
  void init() { std::memset(p, 0, sizeof(p)), cnt = 0; }
  bool insert(u64 val) {
    for (int i = 63; ~i; i--) {
      if (!(val & (1ull << i))) continue;
      if (!p[i]) {
        p[i] = val, cnt++;
        return true;
      }
      val ^= p[i];
    }
    return false;
  }
};
}
constexpr int N = 1e5 + 50, mod = 1e9 + 7;
int n, m;
std::vector<pil> adj[N];
bool vis[N];
i64 dis[N], ans;
int cnt, s[N];
VECSPACE::LinearBasis lb;
void dfs(int u, i64 cur) {
  vis[u] = true, dis[u] = cur, s[++cnt] = u;
  for (auto [v, w] : adj[u]) {
    if (!vis[v]) dfs(v, cur ^ w);
    else lb.insert(cur ^ dis[v] ^ w);
  }
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    i64 w;
    std::cin >> u >> v >> w;
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    lb.init(), cnt = 0, dfs(i, 0);
    for (int j = 0; j < 64; j++) {
      bool flg = false;
      for (int k = 0; k < 64; k++) {
        if (lb.p[k] & (1ll << j)) {
          flg = true;
          break;
        }
      }
      if (flg) {
        (ans += 1ll * cnt * (cnt - 1) / 2 % mod *
                ((1ll << (lb.cnt - 1)) % mod) % mod * ((1ll << j) % mod) %
                mod) %= mod;
      } else {
        int c = 0;
        for (int k = 1; k <= cnt; k++) {
          if (dis[s[k]] & (1ll << j)) c++;
        }
        (ans += 1ll * c * (cnt - c) % mod * ((1ll << lb.cnt) % mod) % mod *
                ((1ll << j) % mod) % mod) %= mod;
      }
    }
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}