/**
 * @file    P6178 【模板】Matrix-Tree 定理.cpp
 * @author  ForgotDream
 * @brief   Matrix Tree Theorem
 * @date    2023-12-08
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 305, mod = 1e9 + 7;
int n, m, t;
i64 a[N][N];
inline i64 fastPow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline i64 getInv(i64 u) { return fastPow(u, mod - 2, mod); }
i64 det(i64 a[N][N]) {
  i64 res = 1, flg = 1;
  for (int i = 1; i < n; i++) {
    int p = -1;
    for (int j = i; j < n; j++) {
      if (a[j][i]) {
        p = j;
        break;
      }
    }
    if (p == -1) return 0;
    if (i != p) std::swap(a[i], a[p]), flg = -flg;
    res = res * a[i][i] % mod;
    i64 inv = getInv(a[i][i]);
    for (int j = i + 1; j < n; j++) a[i][j] = a[i][j] * inv % mod;
    for (int j = i + 1; j < n; j++) {
      if (!a[j][i]) continue;
      for (int k = i + 1; k < n; k++) {
        a[j][k] = (a[j][k] - a[j][i] * a[i][k] % mod + mod) % mod;
      }
    }
  }
  return (res * flg + mod) % mod;
}
void solve() {
  std::cin >> n >> m >> t;
  for (int i = 1, u, v, w; i <= m; i++) {
    std::cin >> u >> v >> w, u--, v--;
    if (t == 0) a[u][v] -= w, a[v][u] -= w, a[u][u] += w, a[v][v] += w;
    else a[u][v] -= w, a[v][v] += w;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) a[i][j] = (a[i][j] + mod) % mod;
  }
  std::cout << det(a) << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
