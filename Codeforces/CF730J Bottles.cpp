/*
 * @file    CF730J Bottles.cpp
 * @author  ForgotDream
 * @brief   Knapsack DP
 * @date    2024-01-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 105, M = 10050;

int n;
struct Bottle {
  int a, b;
  bool operator<(const Bottle &rhs) const {
    return b > rhs.b || (b == rhs.b && a > rhs.a);
  }
} a[N];
int f[M], g[M];

// 你先考虑把至少需要多少个罐子算出来吧。
// 这个直接贪心就行了吧。

void solve() {
  std::cin >> n;
  int tot = 0, m = 0;
  for (int i = 1; i <= n; i++) std::cin >> a[i].a, tot += a[i].a;
  for (int i = 1; i <= n; i++) std::cin >> a[i].b, m += a[i].b;
  std::sort(a + 1, a + n + 1);

  memset(f, 0x3f, sizeof(f)), f[0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = m; j >= a[i].b; j--) {
      if ((f[j - a[i].b] + 1 < f[j]) ||
          (f[j - a[i].b] + 1 == f[j] && g[j - a[i].b] + a[i].a > g[j])) {
        f[j] = f[j - a[i].b] + 1;
        g[j] = g[j - a[i].b] + a[i].a;
      }
    }
  }

  int cnt = 1e9, vol = 0;
  for (int i = tot; i <= m; i++) {
    if (f[i] < cnt || (f[i] == cnt && vol < g[i])) {
      cnt = f[i], vol = g[i];
    }
  }

  std::cout << cnt << " " << tot - vol << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
