/**
 * @file    P3423 BAN-Bank Notes.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> b(n), c(n);
  for (int i = 0; i < n; i++) { std::cin >> b[i]; }
  for (int i = 0; i < n; i++) { std::cin >> c[i]; }

  int k;
  std::cin >> k;

  std::vector f(n, std::vector<int>(k + 1, inf));
  std::vector pre(n, std::vector<int>(k + 1));
  for (int i = 0; i <= c[0] && i * b[0] <= k; i++) { f[0][i * b[0]] = i; }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= k; j++) {
      for (int l = 0; l <= c[i] && l * b[i] <= j; l++) {
        if (f[i - 1][j - l * b[i]] + l < f[i][j]) {
          f[i][j] = f[i - 1][j - l * b[i]] + l;
          pre[i][j] = j - l * b[i];
        }
      }
    }
  }

  std::cout << f[n - 1][k] << "\n";
  std::stack<int> s;
  int cur = k;
  for (int i = n - 1; ~i; i--) {
    int p = pre[i][cur];
    s.push((cur - p) / b[i]), cur = p;
  }
  while (!s.empty()) { std::cout << s.top() << " ", s.pop(); }
  std::cout << "\n";

  return 0;
}