/**
 * @file    CF817D Imbalanced Array.cpp
 * @author  ForgotDream
 * @brief   Monotone Stack
 * @date    2023-05-26
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::stack<int> min, max;
  std::vector<int> minl(n), maxl(n);
  for (int i = 0; i < n; i++) {
    while (!min.empty() && a[min.top()] > a[i]) {
      min.pop();
    }
    while (!max.empty() && a[max.top()] <= a[i]) {
      max.pop();
    }
    minl[i] = min.empty() ? i + 1 : i - min.top();
    maxl[i] = max.empty() ? i + 1 : i - max.top();
    min.push(i), max.push(i);
  }

  while (!min.empty()) {
    min.pop();
  }
  while (!max.empty()) {
    max.pop();
  }

  std::vector<int> minr(n), maxr(n);
  for (int i = n - 1; i >= 0; i--) {
    while (!min.empty() && a[min.top()] >= a[i]) {
      min.pop();
    }
    while (!max.empty() && a[max.top()] < a[i]) {
      max.pop();
    }
    minr[i] = min.empty() ? n - i : min.top() - i;
    maxr[i] = max.empty() ? n - i : max.top() - i;
    min.push(i), max.push(i);
  }

  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    ans += 1ll * (1ll * maxl[i] * maxr[i] - 1ll * minl[i] * minr[i]) * a[i];
  }

  std::cout << ans << "\n";

  return 0;
}