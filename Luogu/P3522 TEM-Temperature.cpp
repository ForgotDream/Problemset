/**
 * @file    P3522 TEM-Temperature.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-21
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace zyz {
constexpr int N = 1e6 + 50;
int n;
int l[N], r[N], q[N];
i64 f[N];

void init() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) { std::cin >> l[i] >> r[i]; }
}

void solve() {
  int p1 = 1, p2 = 1;
  for (int i = 1; i <= n; i++) {
    while (p1 <= p2 && l[q[p1]] > r[i]) { ++p1; }
    if (p1 <= p2) { f[i] = i - q[p1 - 1]; }
    else { f[i] = 1; }
    while (p1 <= p2 && l[q[p2]] < l[i]) { --p2; }
    q[++p2] = i;
  }
  std::cout << *std::max_element(f + 1, f + n + 1) << "\n";
}
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  zyz::init();
  zyz::solve();

  return 0;
}
