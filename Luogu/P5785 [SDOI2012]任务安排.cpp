/**
 * @file    P5785 [SDOI2012]任务安排.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-07-06
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

constexpr int N = 3e5 + 50;
int n;
i64 s, t[N], c[N], f[N];

int q[N], p1 = 1, p2 = 1;
i64 X(int i) { return c[i]; }
i64 Y(int i) { return f[i] - c[i] * s; }
f80 slope(int i, int j) { return 1. * (Y(i) - Y(j)) / (X(i) - X(j)); }
int find(int l, int r, i64 val) {
  int idx = p2;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (Y(q[mid + 1]) - Y(q[mid]) > val * (X(q[mid + 1]) - X(q[mid]))) {
      idx = mid, r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return q[idx];
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> n >> s;
  for (int i = 1; i <= n; i++) {
    std::cin >> t[i] >> c[i];
    t[i] += t[i - 1], c[i] += c[i - 1];
  }

  for (int i = 1; i <= n; i++) {
    int j = find(p1, p2, t[i]);
    f[i] = f[j] + t[i] * (c[i] - c[j]) + s * (c[n] - c[j]);
    while (p1 < p2 && 
        (Y(q[p2]) - Y(q[p2 - 1])) * (X(i) - X(q[p2])) >= 
        (Y(i) - Y(q[p2])) * (X(q[p2]) - X(q[p2 - 1]))) {
      p2--;
    }
    q[++p2] = i;
  }

  std::cout << f[n] << "\n";

  return 0;
}