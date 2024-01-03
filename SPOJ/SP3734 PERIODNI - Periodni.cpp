/*
 * @file    SP3734 PERIODNI - Periodni.cpp
 * @author  ForgotDream
 * @brief   DP + Cartesian Tree
 * @date    2024-01-01
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 550, M = 1e6 + 50, mod = 1e9 + 7;
int n, k, a[N];

std::vector<int> adj[N];

i64 fac[M], ifc[M];
inline i64 fastPow(i64 base, i64 exp, i64 mod) {
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
inline i64 C(i64 n, i64 m) { return fac[n] * ifc[m] % mod * ifc[n - m] % mod; }

int ch[N][2];
inline int &lc(int u) { return ch[u][0]; }
inline int &rc(int u) { return ch[u][1]; }

int st[N], top;
int build() {
  for (int i = 1; i <= n; i++) {
    while (top && a[st[top]] > a[i]) lc(i) = st[top--];
    if (top) rc(st[top]) = i;
    st[++top] = i;
  }
  return st[1];
}

i64 f[N][N], siz[N];
void dfs(int u, int frm) {
  f[u][0] = siz[u] = 1;
  if (lc(u)) {
    dfs(lc(u), u), siz[u] += siz[lc(u)];
    for (int i = std::min(siz[u], 1ll * k); i; i--) {
      for (int j = 1; j <= std::min(siz[lc(u)], 1ll * i); j++) {
        f[u][i] = (f[u][i] + f[lc(u)][j] * f[u][i - j] % mod) % mod;
      }
    }
  }
  if (rc(u)) {
    dfs(rc(u), u), siz[u] += siz[rc(u)];
    for (int i = std::min(siz[u], 1ll * k); i; i--) {
      for (int j = 1; j <= std::min(siz[rc(u)], 1ll * i); j++) {
        f[u][i] = (f[u][i] + f[rc(u)][j] * f[u][i - j] % mod) % mod;
      }
    }
  }
  for (int i = std::min(siz[u], 1ll * k); i; i--) {
    for (int j = 1; j <= std::min(i, a[u] - a[frm]); j++) {
      i64 cur = fac[j] * f[u][i - j] % mod;
      cur = cur * C(a[u] - a[frm], j) % mod * C(siz[u] - i + j, j) % mod;
      f[u][i] = (f[u][i] + cur) % mod;
    }
  }
}

void solve() {
  init(1e6);

  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];

  int rt = build();
  dfs(rt, 0);
  std::cout << f[rt][k] << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
