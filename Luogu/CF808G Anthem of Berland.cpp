/*
 * @file    CF808G Anthem of Berland.cpp
 * @author  ForgotDream
 * @brief   KMP + DP
 * @date    2024-01-11
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 50;

int n, m;
char s[N], t[N];

int nxt[N];
int f[N], g[N];

inline bool check(int p) {
  for (int i = p; i >= p - m + 1; i--) {
    if (s[i] != t[i - p + m] && s[i] != '?') return false;
  }
  return true;
}

void solve() {
  std::cin >> (s + 1) >> (t + 1);
  n = strlen(s + 1), m = strlen(t + 1);

  for (int i = 2, j = nxt[i - 1]; i <= m; i++) {
    while (j && t[i] != t[j + 1]) j = nxt[j];
    if (t[i] == t[j + 1]) j++;
    nxt[i] = j;
  }

  for (int i = 1; i <= n; i++) {
    f[i] = f[i - 1];
    if (!check(i)) continue;
    g[i] = f[i - m] + 1;
    for (int j = nxt[m]; j; j = nxt[j]) {
      g[i] = std::max(g[i], g[i - (m - j)] + 1);
    }
    f[i] = std::max(f[i], g[i]);
  }
  std::cout << f[n] << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
