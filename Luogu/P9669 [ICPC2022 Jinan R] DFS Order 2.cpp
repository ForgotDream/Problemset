/**
 * @file    P9669 [ICPC2022 Jinan R] DFS Order 2.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-10-04
 */
#include <cstring>
#include <iostream>
#include <vector>

using i64 = long long;

constexpr int N = 550, mod = 998244353;
// --- Mod Utils ---
i64 fac[N], ifc[N];
i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
void init(int n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[n] = fastPow(fac[n], mod - 2, mod);
  for (int i = n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}
// -----------------
int n;
std::vector<int> adj[N];
int cnt[N];
i64 siz[N], h[N], f[N][N], g[N], dp[N][N];
void dfs1(int u, int frm) {
  siz[u] = 1, h[u] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs1(v, u);
    siz[u] += siz[v], cnt[u]++;
    h[u] = h[u] * h[v] % mod;
  }
  h[u] = h[u] * fac[cnt[u]] % mod;
}
void dfs2(int u, int frm) {
  std::memset(f, 0, sizeof(f));
  f[0][0] = 1;
  for (auto v : adj[u]) {
    if (v == frm) continue;
    for (int i = cnt[u]; i; i--) {
      for (int j = siz[u]; j >= siz[v]; j--) {
        f[i][j] = (f[i][j] + f[i - 1][j - siz[v]]) % mod;
      }
    }
  }
  for (auto v : adj[u]) {
    if (v == frm) continue;
    for (int i = 1; i <= cnt[u]; i++) {
      for (int j = siz[v]; j <= siz[u]; j++) {
        f[i][j] = (f[i][j] - f[i - 1][j - siz[v]] + mod) % mod;
      }
    }
    std::memset(g, 0, sizeof(g));
    for (int i = 0; i <= siz[u]; i++) {
      for (int j = 0; j < siz[u]; j++) {
        g[i] = (g[i] + fac[j] * fac[cnt[u] - j - 1] % mod * f[j][i] % mod) % mod;
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        dp[v][j] = (dp[v][j] + dp[u][i] * g[j - i - 1] % mod) % mod;
      }
    }
    for (int i = cnt[u]; i; i--) {
      for (int j = siz[u]; j >= siz[v]; j--) {
        f[i][j] = (f[i][j] + f[i - 1][j - siz[v]]) % mod;
      }
    }
  }
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs2(v, u);
  }
}
void solve() {
  std::cin >> n;
  init(n);
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs1(1, 0), dp[1][1] = h[1], dfs2(1, 0);
  for (int i = 1; i <= n; i++) {
    i64 sum = 0;
    for (int j = 1; j <= n; j++) (sum += dp[i][j]) %= mod;
    i64 inv = fastPow(sum, mod - 2, mod);
    for (int j = 1; j <= n; j++) {
      std::cout << dp[i][j] * dp[1][1] % mod * inv % mod << " \n"[j == n];
    }
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
