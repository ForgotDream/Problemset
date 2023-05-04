/**
 * @file    CF1656B Subtract Operation.cpp
 * @author  ForgotDream
 * @brief   Sorting + Two Pointers
 * @date    2023-05-04
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

void solve() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  if (n == 1) {
    if (a[0] == k) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
    return;
  }

  std::sort(a.begin(), a.end());

  for (int i = 0, j = 0; i < n; i++) {
    while (j < n && std::abs(a[i] - a[j]) < k) {
      j++;
    }
    if (j == n) {
      break;
    }
    if (std::abs(a[i] - a[j]) == k) {
      std::cout << "YES\n";
      return;
    }
  }

  std::cout << "NO\n";

  return;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}