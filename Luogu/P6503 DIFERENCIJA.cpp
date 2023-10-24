/**
 * @file    P6503 DIFERENCIJA.cpp
 * @author  ForgotDream
 * @brief   Monotone Stack
 * @date    2023-05-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<i64> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::stack<int> s_max, s_min;
  std::vector p(4, std::vector<i64>(n));
  for (int i = 0; i < n; i++) {
    while (!s_max.empty() && a[s_max.top()] <= a[i]) {
      s_max.pop();
    }
    if (s_max.empty()) {
      p[0][i] = i;
    } else {
      p[0][i] = i - s_max.top() - 1;
    }
    s_max.push(i);

    while (!s_min.empty() && a[s_min.top()] >= a[i]) {
      s_min.pop();
    }
    if (s_min.empty()) {
      p[2][i] = i;
    } else {
      p[2][i] = i - s_min.top() - 1;
    }
    s_min.push(i);
  }

  while (!s_max.empty()) {
    s_max.pop();
  }
  while (!s_min.empty()) {
    s_min.pop();
  }

  for (int i = n - 1; i >= 0; i--) {
    while (!s_max.empty() && a[s_max.top()] < a[i]) {
      s_max.pop();
    }
    if (s_max.empty()) {
      p[1][i] = n - i - 1;
    } else {
      p[1][i] = s_max.top() - i - 1;
    }
    s_max.push(i);

    while (!s_min.empty() && a[s_min.top()] > a[i]) {
      s_min.pop();
    }
    if (s_min.empty()) {
      p[3][i] = n - i - 1;
    } else {
      p[3][i] = s_min.top() - i - 1;
    }
    s_min.push(i);
  }

  i64 max = 0, min = 0;
  for (int i = 0; i < n; i++) {
    max += (p[0][i] + 1) * (p[1][i] + 1) * a[i];
    min += (p[2][i] + 1) * (p[3][i] + 1) * a[i];
  }

  std::cout << max - min << "\n";

  return 0;
}