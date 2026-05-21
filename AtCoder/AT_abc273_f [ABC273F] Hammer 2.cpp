/*
 * @file    AT_abc273_f [ABC273F] Hammer 2.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2024-02-29
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

template <typename T>
inline bool chkmin(T &x, const T &y) { return x > y ? x = y, true : false; }

constexpr int N = 3050;

int n, m, p;
int x[N], y[N];

struct Atom {
  int pos, id;
  friend bool operator<(const Atom &lhs, const Atom &rhs) {
    return lhs.pos < rhs.pos;
  }
} a[N];
i64 f[N][N][2];

void solve() {
  std::cin >> n >> p;
  for (int i = 1; i <= n; i++) std::cin >> x[i], a[++m] = {x[i], i};
  for (int i = 1; i <= n; i++) std::cin >> y[i], a[++m] = {y[i], 0};
  a[++m] = {0, 0}, a[++m] = {p, 0};
  std::sort(a + 1, a + m + 1);

  memset(f, 0x3f, sizeof(f));

  int s = 0, t = 0;
  for (int i = 1; i <= m; i++) if (a[i].pos == 0) s = i;
  for (int i = 1; i <= m; i++) if (a[i].pos == p) t = i;

  f[s][s][0] = f[s][s][1] = 0;
  for (int len = 1; len <= m; len++) {
    for (int l = 1, r = l + len - 1; r <= m; l++, r++) {
      if (l > 1) {
        int d = y[a[l - 1].id];
        if (!(a[l - 1].id && (d < a[l].pos || a[r].pos < d))) {
          chkmin(f[l - 1][r][0], f[l][r][0] + a[l].pos - a[l - 1].pos);
          chkmin(f[l - 1][r][0], f[l][r][1] + a[r].pos - a[l - 1].pos);
        }
      }
      if (r < m) {
        int d = y[a[r + 1].id];
        if (!(a[r + 1].id && (d < a[l].pos || a[r].pos < d))) {
          chkmin(f[l][r + 1][1], f[l][r][0] + a[r + 1].pos - a[l].pos);
          chkmin(f[l][r + 1][1], f[l][r][1] + a[r + 1].pos - a[r].pos);
        }
      }
    }
  }

  i64 ans = 1e18;
  for (int i = 1; i <= t; i++) {
    for (int j = t; j <= m; j++) {
      ans = std::min({ans, f[i][j][0], f[i][j][1]});
    }
  }
  if (ans == 1e18) std::cout << -1 << "\n";
  else std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
