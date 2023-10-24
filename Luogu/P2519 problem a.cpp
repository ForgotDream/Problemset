/**
 * @file    P2519 problem a.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-26
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].first >> a[i].second;
    a[i].first = a[i].first + 1;
    a[i].second = n - a[i].second;
  }

  std::sort(a.begin(), a.end());
  std::vector<std::pair<int, int>> b;
  for (int i = 0; i < n; i++) {
    if (a[i].first <= a[i].second) {
      b.emplace_back(a[i]);
    }
  }

  std::vector<std::tuple<int, int, int>> c;
  for (int i = 0; i < b.size(); i++) {
    if (i == 0 || b[i] != b[i - 1]) {
      c.emplace_back(b[i].first, b[i].second, 1);
    } else if (auto &[l, r, v] = c[c.size() - 1]; r - l + 1> v) {
      v++;
    }
  }

  std::sort(c.begin(), c.end(), [&](auto lhs, auto rhs) {
    if (std::get<1>(lhs) == std::get<1>(rhs)) {
      return std::get<0>(lhs) < std::get<0>(rhs);
    }
    return std::get<1>(lhs) < std::get<1>(rhs);
  });

  std::vector<int> f(c.size());
  f[0] = std::get<2>(c[0]);

  auto find = [&](int l, int r, int v) {
    while (l <= r) {
      int mid = (l + r) >> 1;
      if (std::get<1>(c[mid]) < v) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return r;
  };

  for (int i = 1; i < c.size(); i++) {
    auto pre = find(0, i - 1, std::get<0>(c[i]));
    f[i] = std::max(f[i - 1], f[pre] + std::get<2>(c[i]));
  }

  std::cout << n - f[c.size() - 1] << "\n";

  return 0;
}
