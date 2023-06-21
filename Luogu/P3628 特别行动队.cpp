/**
 * @file    P3628 特别行动队.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-21
 */
#include <bits/stdc++.h>

using i64 = long long;

namespace zyz {
constexpr int N = 1e6 + 50;
int n, a, b, c;
int x[N], q[N];
i64 f[N], s[N];

inline i64 X(int i) { return 2 * a * s[i]; }
inline i64 Y(int i) { return f[i] + a * s[i] * s[i] - b * s[i]; }
inline i64 up(int i, int j) { return Y(i) - Y(j); }
inline i64 down(int i, int j) { return X(i) - X(j); }

void init() {
  std::cin >> n >> a >> b >> c;
  for (int i = 1; i <= n; i++) { std::cin >> x[i]; }
}

void solve() {
  std::partial_sum(x + 1, x + n + 1, s + 1);

  int p1 = 1, p2 = 1;
  for (int i = 1; i <= n; i++) {
    while (p1 < p2 && up(q[p1 + 1], q[p1]) >= s[i] * down(q[p1 + 1], q[p1])) {
      p1++;
    }
    int j = q[p1];
    f[i] = f[j] + a * (s[i] - s[j]) * (s[i] - s[j]) + b * (s[i] - s[j]) + c;
    while (p1 < p2 && 
        down(q[p2], q[p2 - 1]) * up(i, q[p2]) <= 
        down(i, q[p2]) * up(q[p2], q[p2 - 1])) {
      p2--;
    }
    q[++p2] = i;
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
