/*
 * @file    P9338 [JOISC 2023 Day3] Chorus.cpp
 * @author  ForgotDream
 * @brief   WQS + DP
 * @date    2024-01-09
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 50;

int n, k, a[N], s[N], p[N];
i64 ss[N];

int q[N], hd, tl;
i64 f[N];
int g[N];

template<typename T>
inline bool chkmin(T &u, const T &v) { return u > v ? u = v, true : false; }
template<typename T>
inline bool chkmax(T &u, const T &v) { return u < v ? u = v, true : false; }

inline i64 x(int u) { return u; }
inline i64 y(int u) { return f[u] + 1ll * u * p[u] - ss[p[u]]; }

int check(i64 u) {
  memset(f, 0x3f, sizeof(f)), f[0] = 0;
  std::fill(g + 1, g + n + 1, k + 1), g[0] = 0;

  q[hd = tl = 1] = 0;
  for (int i = 1; i <= n; i++) {
    while (hd < tl && 
           i * (x(q[hd + 1]) - x(q[hd])) > y(q[hd + 1]) - y(q[hd])) {
      hd++;
    }
    int j = q[hd];
    f[i] = f[j] + ss[i] - ss[p[j]] - 1ll * (i - p[j]) * j - u;
    g[i] = g[j] + 1;
    while (hd < tl && 
           (y(i) - y(q[tl])) * (x(q[tl]) - x(q[tl - 1])) < 
               (x(i) - x(q[tl])) * (y(q[tl]) - y(q[tl - 1]))) {
      tl--;
    }
    q[++tl] = i;
  }
  return g[n];
}

void solve() {
  std::cin >> n >> k;
  std::iota(p + 1, p + n + 1, 1);

  int cnt = 0;
  for (int i = 1; i <= 2 * n; i++) {
    char c; std::cin >> c;
    if (c == 'A') {
      cnt++;
      s[cnt + 1] = s[cnt], ss[cnt + 1] = ss[cnt] + s[cnt + 1];
    } else {
      s[cnt + 1]++, ss[cnt + 1]++;
      chkmax(p[s[cnt + 1]], cnt);
    }
  }

  i64 lo = -1e18, hi = 0, ans = 0;
  while (lo <= hi) {
    i64 mid = (lo + hi) >> 1;
    if (check(mid) <= k) lo = mid + 1, ans = mid;
    else hi = mid - 1;
  }

  check(ans);
  std::cout << f[n] + k * ans << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
