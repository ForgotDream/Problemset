/*
 * @file    P5308 [COCI2018-2019#4] Akvizna.cpp
 * @author  ForgotDream
 * @brief   DP + WQS Binary Search
 * @date    2024-02-28
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using f96 = long double;

constexpr int N = 1e5 + 50;
constexpr f96 eps = 1e-16;

int n, k;

f96 f[N];
int g[N];

inline bool chkmax(f96 &u, const f96 &v) {
  if (u + eps < v) return u = v, true;
  else return false;
}

int q[N], hd, tl;

inline f96 slope(int i, int j) { return (f[i] - f[j]) / (i - j); }

bool check(f96 u) {
  std::cerr << u << "\n";
  q[hd = tl = 1] = 0;
  for (int i = 1; i <= n; i++) {
    while (hd < tl && slope(q[hd], q[hd + 1]) > f96(1) / i + eps) hd++;
    int j = q[hd];
    f[i] = f[j] + 1 - f96(j) / i - u, g[i] = g[j] + 1;
    while (hd < tl && slope(q[tl - 1], q[tl]) + eps < slope(q[tl], i)) tl--;
    q[++tl] = i;
  }
  return g[n] >= k;
}

void solve() {
  std::cin >> n >> k;

  f96 lo = 0, hi = 1e6, ans = 0;
  while (std::abs(lo - hi) > eps) {
    f96 mid = (lo + hi) / 2;
    if (check(mid)) lo = mid, ans = f[n] + k * mid;
    else hi = mid;
  }

  std::cout << std::fixed << std::setprecision(9) << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
