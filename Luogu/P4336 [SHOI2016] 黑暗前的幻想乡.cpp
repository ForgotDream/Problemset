/**
 * @file    P4336 [SHOI2016] 黑暗前的幻想乡.cpp
 * @author  ForgotDream
 * @brief   Matrix Tree Theorem + Inclusion-Exclusion Principle
 * @date    2023-12-07
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 20, M = 200, mod = 1e9 + 7;
int n, siz[N], u[N][M], v[N][M];
i64 g[N][N];
inline i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline i64 getInv(i64 u) { return fastPow(u, mod - 2, mod); }
i64 det(i64 g[N][N]) {
  for (int i = 1; i < n; i++) for (int j = 1; j < n; j++) g[i][j] = (g[i][j] + mod) % mod;
  i64 res = 1, flg = 1;
  for (int i = 1; i < n; i++) {
    int p = -1;
    for (int j = i; j < n; j++) {
      if (g[j][i]) {
        p = j;
        break;
      }
    }
    if (p == -1) return 0;
    res = res * g[p][p] % mod;
    if (i != p) std::swap(g[i], g[p]), flg = -flg;
    i64 inv = getInv(g[i][i]);
    for (int j = i + 1; j < n; j++) g[i][j] = g[i][j] * inv % mod;
    for (int j = i + 1; j < n; j++) {
      if (!g[j][i]) continue;
      for (int k = i + 1; k < n; k++) {
        g[j][k] = (g[j][k] - g[j][i] * g[i][k] % mod + mod) % mod;
      }
    }
  }
  return (res * flg + mod) % mod;
}
void solve() {
  std::cin >> n;
  for (int i = 0; i < n - 1; i++) {
    std::cin >> siz[i];
    for (int j = 1; j <= siz[i]; j++) std::cin >> u[i][j] >> v[i][j];
  }
  int mask = (1 << (n - 1)) - 1;
  i64 ans = 0;
  for (int st = 0; st <= mask; st++) {
    memset(g, 0, sizeof(g));
    for (int i = 0; i < n - 1; i++) {
      if (!(st & (1 << i))) continue;
      for (int j = 1; j <= siz[i]; j++) {
        g[u[i][j]][v[i][j]]--, g[v[i][j]][u[i][j]]--;
        g[u[i][j]][u[i][j]]++, g[v[i][j]][v[i][j]]++;
      }
    }
    int cnt = __builtin_popcount(st);
    i64 cur = det(g);
    // std::cerr << cur << "\n";
    (ans += cur * ((n - cnt) & 1 ? 1 : -1)) %= mod;
  }
  std::cout << (ans + mod) % mod << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
