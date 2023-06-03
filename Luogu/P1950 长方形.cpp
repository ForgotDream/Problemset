/**
 * @file    P1950 长方形.cpp
 * @author  ForgotDream
 * @brief   Monotone Stack
 * @date    2023-05-26
 */
#include <bits/stdc++.h>

using i64 = long long;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector a(n, std::vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      char c;
      std::cin >> c;
      a[i][j] = (c == '*');
    }
  }

  i64 ans = 0;
  std::vector<int> h(m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j]) {
        h[j] = 0;
      } else {
        h[j]++;
      }
    }

    std::stack<int> s;
    std::vector<int> l(m), r(m);
    for (int j = 0; j < m; j++) {
      while (!s.empty() && h[s.top()] > h[j]) {
        r[s.top()] = j;
        s.pop();
      }
      s.push(j);
    }
    while (!s.empty()) {
      r[s.top()] = m;
      s.pop();
    }

    for (int j = m - 1; j >= 0; j--) {
      while (!s.empty() && h[s.top()] >= h[j]) {
        l[s.top()] = j;
        s.pop();
      }
      s.push(j);
    }
    while (!s.empty()) {
      l[s.top()] = -1;
      s.pop();
    }

    for (int j = 0; j < m; j++) {
      ans += 1ll * (r[j] - j) * (j - l[j]) * h[j];
    }
  }

  std::cout << ans << "\n";

  return 0;
}