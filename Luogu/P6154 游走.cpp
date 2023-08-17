/**
 * @file    P6154 游走.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-08-16
 */
#include <iostream>
#include <vector>
#include <queue>

using i64 = long long;

constexpr int N = 1e5 + 50, mod = 998244353;
int n, m;
std::vector<int> adj[N], rev[N];
int deg[N];
i64 f[N], g[N];

// invertion
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
i64 inv(i64 num) { return fastPow(num, mod - 2, mod); }

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), deg[v]++;
    rev[v].push_back(u);
  }

  std::queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!deg[i]) q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop(), g[u] = 1;
    for (auto v : rev[u]) {
      (f[u] += f[v] + g[v]) %= mod;
      (g[u] += g[v]) %= mod;
    }
    for (auto v : adj[u]) {
      if (!--deg[v]) q.push(v);
    }
  }

  i64 ans = 0, path = 0;
  for (int i = 1; i <= n; i++) (ans += f[i]) %= mod, (path += g[i]) %= mod;
  std::cerr << ans << " " << path << "\n";
  (ans *= inv(path)) %= mod;
  std::cout << ans << "\n";

  return 0;
}