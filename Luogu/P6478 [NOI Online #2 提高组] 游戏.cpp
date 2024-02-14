/*
 * @file    P6478 [NOI Online #2 提高组] 游戏.cpp
 * @author  ForgotDream
 * @brief   DP + Binomial Inversion
 * @date    2024-02-14
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

constexpr int N = 5050, mod = 998244353;

int n, typ[N];
std::vector<int> adj[N];

int siz[N];
i64 f[N][N], tmp[N];

void dfs(int u, int frm) {
  siz[u] = 1, f[u][0] = 1;
  bool flg = typ[u];
  for (auto v : adj[u]) {
    if (v == frm) continue;
    dfs(v, u);
    std::fill(tmp, tmp + siz[u] + siz[v] + 1, 0);
    for (int i = 0; i <= std::min(siz[u], n / 2); i++) {
      for (int j = 0; j <= std::min(siz[v], n / 2 - i); j++) {
        tmp[i + j] += f[u][i] * f[v][j] % mod;
        tmp[i + j] %= mod;
      }
    }
    std::copy(tmp, tmp + siz[u] + siz[v] + 1, f[u]);
    siz[u] += siz[v], typ[u] += typ[v];
  }
  for (int i = std::min({siz[u], siz[u] - typ[u], n / 2}); i; i--) {
    if (flg) {
      f[u][i] += f[u][i - 1] * (siz[u] - typ[u] - (i - 1)) % mod;
    } else {
      f[u][i] += f[u][i - 1] * (typ[u] - (i - 1)) % mod;
    }
    f[u][i] %= mod;
  }
}

i64 fac[N], ifc[N];

inline i64 fast_pow(i64 base, i64 exp, i64 mod) {
  i64 res = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) (res *= base) %= mod;
    (base *= base) %= mod;
  }
  return res;
}

void init(int _n) {
  fac[0] = ifc[0] = 1;
  for (int i = 1; i <= _n; i++) fac[i] = i * fac[i - 1] % mod;
  ifc[_n] = fast_pow(fac[_n], mod - 2, mod);
  for (int i = _n - 1; i; i--) ifc[i] = (i + 1) * ifc[i + 1] % mod;
}

inline i64 C(i64 n, i64 m) { return fac[n] * ifc[m] % mod * ifc[n - m] % mod; }

void solve() {
  std::cin >> n;
  init(n / 2);

  for (int i = 1; i <= n; i++) {
    char c;
    std::cin >> c;
    typ[i] = c - '0';
  }
  for (int i = 1, u, v; i < n; i++) {
    std::cin >> u >> v;
    adj[u].push_back(v), adj[v].push_back(u);
  }

  dfs(1, 0);
  for (int i = 0; i <= n / 2; i++) f[1][i] = f[1][i] * fac[n / 2 - i] % mod;

  for (int i = 0; i <= n / 2; i++) {
    i64 ans = 0;
    for (int j = i; j <= n / 2; j++) {
      ans += ((j - i) & 1 ? mod - 1 : 1) * C(j, i) % mod * f[1][j] % mod;
      ans %= mod;
    }
    std::cout << ans << "\n";
  }
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
