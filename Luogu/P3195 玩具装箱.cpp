/**
 * @file    P3195 玩具装箱.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-21
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace zyz {
constexpr int N = 5e4 + 50;
int n, l;
i64 f[N], c[N], sum[N], s[N];
int dq[N];

inline i64 X(int i) { return 2 * s[i]; }
inline i64 Y(int i) { return f[i] + s[i] * s[i] + 2 * s[i] * l; }
inline i64 up(int i, int j) { return Y(i) - Y(j); }
inline i64 down(int i, int j) { return X(i) - X(j); }

void init() {
  std::cin >> n >> l;
  for (int i = 1; i <= n; i++) { std::cin >> c[i]; }
}

void solve() {
  std::memset(f, 0x3f, sizeof(f)), f[0] = 0;
  std::partial_sum(c + 1, c + n + 1, sum + 1);
  for (int i = 1; i <= n; i++) { s[i] = i + sum[i]; }
  ++l;

  int p1 = 1, p2 = 1;
  for (int i = 1; i <= n; i++) {
    while (p1 < p2 && 
        up(dq[p1 + 1], dq[p1]) <= s[i] * down(dq[p1 + 1], dq[p1])) {
      ++p1;
    }
    f[i] = f[dq[p1]] + (s[i] - s[dq[p1]] - l) * (s[i] - s[dq[p1]] - l);
    while (p1 < p2 && 
        down(dq[p2], dq[p2 - 1]) * up(i, dq[p2]) <= 
        up(dq[p2], dq[p2 - 1]) * down(i, dq[p2])) {
      --p2;
    }
    dq[++p2] = i;
  }

  std::cout << f[n] << "\n";
}
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  zyz::init();
  zyz::solve();

  return 0;
}
