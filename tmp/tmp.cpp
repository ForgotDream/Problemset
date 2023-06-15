/**
 * @file    
 * @author  ForgotDream
 * @brief   
 * @date    2023-06-15
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int mod = 1e9 + 7;

auto solve(const std::vector<std::vector<int>> &a) {
  assert(!a.empty());
  int n = a.size(), m = a[0].size();
  std::vector f(n, std::vector(m, std::vector<i64>(1 << m)));
  auto pre = [&](int i, int j, int st) {
    if (i == 0 && j == 0) {
      if (st == 0) {
        return 1ll;
      } else {
        return 0ll;
      }
    }
    if (j == 0) {
      return f[i - 1][m - 1][st];
    } else {
      return f[i][j - 1][st];
    }
  };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int st = 0; st < 1 << m; st++) {
        i64 preVal = pre(i, j, st);
        if (!a[i][j]) {
          if ((st >> j) & 1) {
            f[i][j][st ^ (1 << j)] += preVal;
          } else {
            f[i][j][st] += preVal;
            if (j != m - 1 && !((st >> j) & 3)) {
              f[i][j][st ^ (1 << (j + 1))] += preVal;
            }
            f[i][j][st ^ (1 << j)] += preVal;
          }
        } else {
          f[i][j][st] += preVal;
        }
      }
    }
  }
  return f;
}

template<typename T>
void reverse(std::vector<std::vector<T>> &a) {
  std::reverse(a.begin(), a.end());
  for (auto &i : a) { std::reverse(i.begin(), i.end()); }
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector a(n, std::vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) { std::cin >> a[i][j]; }
  }

  auto f = solve(a);
  reverse(a);
  auto g = solve(a);
  reverse(g);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) { 
      std::cerr << "[" << i << ", " << j << "]: ";
      for (int k = 0; k < (1 << m); k++) {
        std::cerr << f[i][j][k] << " \n"[k == (1 << m) - 1];
      }
    }
  }
  std::cerr << "\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) { 
      std::cerr << "[" << i << ", " << j << "]: ";
      for (int k = 0; k < (1 << m); k++) {
        std::cerr << g[i][j][k] << " \n"[k == (1 << m) - 1];
      }
    }
  }

  reverse(a);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j]) {
        std::cout << 0 << " \n"[j == m - 1];
      } else {
        i64 ans = 0;
        int prex = (j == 0 ? i - 1 : i), prey = (j == 0 ? m - 1 : j - 1);
        int nxtx = (j == m - 1 ? i + 1 : i), nxty = (j == m - 1 ? 0 : j + 1);
        int st = ((1 << m) - 1) ^ (1 << j);
        for (int k = st; k; k = (k - 1) & st) {
          i64 pre = (i == 0 && j == 0 ? 1 : f[prex][prey][k]);
          i64 nxt = (i == n - 1 && j == m - 1 ? 1 : g[nxtx][nxty][k]);
          (ans += pre * nxt % mod) %= mod;
        }
        i64 pre = (i == 0 && j == 0 ? 1 : f[prex][prey][0]);
        i64 nxt = (i == n - 1 && j == m - 1 ? 1 : g[nxtx][nxty][0]);
        (ans += pre * nxt % mod) %= mod;
        std::cout << ans % mod << " \n"[j == m - 1];
      }
    }
  }

  return 0;
}