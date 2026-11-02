/*
 * @file    LOJ#5047 「JOISC 2025 Day2」救护车.cpp
 * @author  ForgotDream
 * @brief   Knapsack DP
 * @date    2026-10-30
 */
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

void solve() {
  int l, n, t;
  std::cin >> l >> n >> t;
  t /= 2;
  
  std::vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
    x[i]--, y[i]--;
  }

  std::vector<int> p0(n), p1(n);
  std::iota(p0.begin(), p0.end(), 0);
  std::iota(p1.begin(), p1.end(), 0);

  std::sort(p0.begin(), p0.end(), [&](auto lhs, auto rhs) {
    return x[lhs] + y[lhs] < x[rhs] + y[rhs];
  });
  std::sort(p1.begin(), p1.end(), [&](auto lhs, auto rhs) {
    return x[lhs] - y[lhs] < x[rhs] - y[rhs];
  });

  std::vector<int> idx0(n);
  for (int i = 0; i < n; i++) idx0[p0[i]] = i;

  auto dis = [&](int d, int u) {
    if (d == 0) return x[u] + y[u];
    else if (d == 1) return x[u] + (l - y[u] - 1);
    else if (d == 2) return (l - x[u] - 1) + (l - y[u] - 1);
    else return (l - x[u] - 1) + y[u];
  };

  std::vector<int> f0(t + 1), f1(t + 1);
  std::vector f2(n + 1, std::vector<int>(t + 1));
  std::vector f3(n + 1, std::vector<int>(t + 1));

  auto modify = [&](std::vector<int> &f, int a, int b) {
    for (int w = t; w >= a; w--) f[w] = std::min(f[w] + b, f[w - a]);
    for (int w = std::min(t, a - 1); ~w; w--) f[w] = f[w] + b;
  };

  for (int s0 = 0; s0 <= n; s0++) {
    std::fill(f2[n].begin(), f2[n].end(), 0);
    std::fill(f3[n].begin(), f3[n].end(), 0);
    for (int i = n - 1; ~i; i--) {
      int u = p1[i];
      f2[i] = f2[i + 1], f3[i] = f3[i + 1];

      if (idx0[u] < s0) modify(f3[i], dis(3, u), dis(0, u));
      else modify(f2[i], dis(2, u), dis(3, u));
    }

    std::fill(f0.begin(), f0.end(), 0);
    std::fill(f1.begin(), f1.end(), 0);
    for (int s1 = 0; s1 <= n; s1++) {
      if (f0[t] <= t && f1[t] <= t && f2[s1][t] <= t && f3[s1][t] <= t) {
        for (int w0 = 0; w0 <= t; w0++) {
          int w1 = t - f0[w0];
          if (w1 < 0) continue;
          int w2 = t - f1[w1];
          if (w2 < 0) continue;
          int w3 = t - f2[s1][w2];
          if (w3 < 0) continue;
          if (t - f3[s1][w3] >= w0) {
            std::cout << "Yes\n";
            return;
          }
        }
      }
      if (s1 < n) {
        int u = p1[s1];
        if (idx0[u] < s0) modify(f0, dis(0, u), dis(1, u));
        else modify(f1, dis(1, u), dis(2, u));
      }
    }
  }

  std::cout << "No\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t = 1;
  // std::cin >> t;
  while (t--) solve();

  return 0;
}
