/**
 * @file    CF1093D Beautiful Graph.cpp
 * @author  ForgotDream
 * @brief   二分图
 * @date    2023-09-05
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 3e5 + 50, mod = 998244353;
int n, m;
std::vector<int> adj[N];
int cnt[2], vis[N];
bool dfs(int u, int col) {
  vis[u] = col, cnt[col]++;
  for (auto v : adj[u]) {
    if (vis[v] != -1) {
      if (vis[v] == col) return false;
      continue;
    }
    if (!dfs(v, col ^ 1)) return false;
  }
  return true;
}
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void solve() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) adj[i].clear(), vis[i] = -1;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  i64 ans = 1;
  for (int i = 1; i <= n; i++) {
    if (vis[i] == -1) {
      cnt[0] = cnt[1] = 0;
      if (!dfs(i, 0)) {
        std::cout << 0 << "\n";
        return;
      }
      ans *= (fastPow(2, cnt[0], mod) + fastPow(2, cnt[1], mod)) % mod;
      ans %= mod;
    }
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}