/*
 * @file    CF1463F Max Correct Set.cpp
 * @author  ForgotDream
 * @brief   DP?
 * @date    2024-01-10
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 55;

int n, x, y;
int cnt[N], f[N][2][2];

int solve(int n, int x, int y) {
  int g = std::gcd(x, y);
  if (g != 1) return (g - n % g) * solve(n / g, x / g, y / g) +
                     (n % g) * solve(n / g + 1, x / g, y / g);
  int s = x + y;
  for (int i = 0; i < s; i++) {
    // [0, n) 区间内有多少个数字 mod (x + y) = i
    cnt[i] = (n - 1) / s + ((n - 1) % s >= i);
  }
  f[0][1][1] = cnt[0];
  for (int i = 1; i < s; i++) {
    int cur = x * i % s;
    if (i != s - 1) f[i][1][1] = f[i - 1][0][1] + cnt[cur];
    f[i][0][1] = std::max(f[i - 1][1][1], f[i - 1][0][1]);
    f[i][1][0] = f[i - 1][0][0] + cnt[cur];
    f[i][0][0] = std::max(f[i - 1][1][0], f[i - 1][0][0]);
  }
  return std::max({f[s - 1][0][0], f[s - 1][0][1], f[s - 1][1][0], 
                   f[s - 1][1][1]});
}

void solve() {
  std::cin >> n >> x >> y;
  std::cout << solve(n, x, y) << "\n";
}

signed main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
