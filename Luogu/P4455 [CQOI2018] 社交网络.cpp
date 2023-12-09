/**
 * @file    P4455 [CQOI2018] 社交网络.cpp
 * @author  ForgotDream
 * @brief   Matrix Tree Theorem
 * @date    2023-12-08
 */
#include <bits/stdc++.h>

using i64 = int64_t;

constexpr int N = 255, mod = 1e4 + 7;
int n, m, a[N][N];
inline int fastPow(int base, int exp, int mod) {
  int res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}
inline int getInv(int u) { return fastPow(u, mod - 2, mod); }
int det(int a[N][N]) {
  int res = 1, flg = 1;
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
    int inv = getInv(a[i][i]);
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
  std::cin >> n >> m;
  for (int i = 1, u, v; i <= m; i++) {
    std::cin >> v >> u, u--, v--;
    // std::cin >> u >> v, u--, v--;
    a[v][v]++, a[u][v]--;
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
