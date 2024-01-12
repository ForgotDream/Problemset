/*
 * @file    P4156 [WC2016] 论战捆竹竿.cpp
 * @author  ForgotDream
 * @brief   弱周期引理 + 基本子串字典 + 同余最短路
 * @date    2024-01-11
 */
#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
inline bool chkmin(T &a, const T &b) { return a > b ? a = b, true : false; }
template <typename T>
inline bool chkmax(T &a, const T &b) { return a < b ? a = b, true : false; }

constexpr int N = 5e5 + 50;
int n;
i64 w;
char s[N];

int nxt[N], period[N], m;

void getBorder() {
  m = 0;
  for (int i = 2, j = nxt[i - 1]; i <= n; i++) {
    while (j && s[i] != s[j + 1]) j = nxt[j];
    if (s[i] == s[j + 1]) j++;
    nxt[i] = j;
  }
  int u = nxt[n];
  while (u) {
    period[++m] = n - u;
    u = nxt[u];
  }
  period[++m] = n;
}

int mod;
i64 f[N], g[N];

void modify(int val) {
  static int cir[2 * N], top;

  int cnt = std::gcd(mod, val);
  std::copy(f, f + mod, g);
  memset(f, 0x3f, sizeof(i64) * val);
  for (int i = 0, t; i < mod; i++) t = g[i] % val, chkmin(f[t], g[i]);
  for (int i = 0; i < cnt; i++) {
    cir[top = 1] = i;
    for (int t = (i + mod) % val; t != i; t = (t + mod) % val) cir[++top] = t;
    std::copy(cir + 1, cir + top + 1, cir + top + 1), top *= 2;
    for (int j = 2; j <= top; j++) chkmin(f[cir[j]], f[cir[j - 1]] + mod);
  }

  mod = val;
  // for (int i = 0; i < mod; i++) std::cerr << f[i] << " \n"[i == mod - 1];
}

void calc(int p, int d, int len) {
  static int cir[N], top, pos[N], hd, tl;
  static i64 val[N];

  modify(p);
  if (d < 0) return;

  int cnt = std::gcd(p, d);
  for (int i = 0; i < cnt; i++) {
    cir[top = 1] = i;
    for (int t = (i + d) % p; t != i; t = (t + d) % p) cir[++top] = t;

    int piv = 1;
    for (int j = 2; j <= top; j++) if (f[cir[j]] < f[cir[piv]]) piv = j;

    std::rotate(cir + 1, cir + piv, cir + top + 1);

    hd = tl = 1, pos[1] = 1, val[1] = f[cir[1]] - d;
    for (int j = 2; j <= top; j++) {
      while (hd <= tl && pos[hd] + len < j) hd++;
      if (hd <= tl) chkmin(f[cir[j]], val[hd] + 1ll * j * d + p);
      while (hd <= tl && val[tl] >= f[cir[j]] - 1ll * j * d) tl--;
      val[++tl] = f[cir[j]] - 1ll * j * d, pos[tl] = j;
    }
  }
}

void solve() {
  std::cin >> n >> w >> (s + 1), w -= n;

  memset(f, 0x3f, sizeof(i64) * n), f[0] = 0;
  mod = n;

  getBorder();
  // for (int i = 1; i <= m; i++) std::cerr << period[i] << " \n"[i == m];

  for (int i = 1, j = 1; i <= m; i = j) {
    while (period[i + 1] - period[i] == period[j + 1] - period[j]) j++;
    calc(period[i], period[i + 1] - period[i], j - i - 1);
  }

  i64 ans = 0;
  for (int i = 0; i < mod; i++) {
    if (f[i] <= w) ans += (w - f[i]) / mod + 1;
  }
  std::cout << ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  std::cin >> t;
  while (t--) solve();

  return 0;
}
