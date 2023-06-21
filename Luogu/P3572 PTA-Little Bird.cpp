/**
 * @file    P3572 PTA-Little Bird.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-21
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace zyz {
constexpr int N = 1e6 + 50;
int n, q;
int d[N], dq[N], f[N];

void init() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) { std::cin >> d[i]; }
  std::cin >> q;
}

int calc(int k) {
  int p1 = 1, p2 = 1;
  dq[p1] = 1, f[1] = 0;
  for (int i = 2; i <= n; i++) {
    while (p1 <= p2 && dq[p1] < i - k) { p1++; }
    f[i] = f[dq[p1]] + (d[dq[p1]] <= d[i]);
    while (p1 <= p2 && 
        (f[dq[p2]] > f[i] || (f[dq[p2]] == f[i] && d[dq[p2]] <= d[i]))) { 
      p2--; 
    }
    dq[++p2] = i;
  }
  // for (int i = 1; i <= n; i++) { std::cerr << f[i] << " \n"[i == n]; }
  return f[n];
}

void solve() {
  while (q--) {
    int k;
    std::cin >> k;
    std::cout << calc(k) << "\n";
  }
}
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  zyz::init();
  zyz::solve();

  return 0;
}
