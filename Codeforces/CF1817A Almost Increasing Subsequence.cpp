/**
 * @file    CF1817A Almost Increasing Subsequence.cpp
 * @author  ForgotDream
 * @brief   Greedy
 * @date    2023-04-30
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

namespace Helper {
void useFileInuput() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif
  return;
}

void debug(const std::string &s) {
  std::clog << s << "\n";
  return;
}
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, q;
  std::cin >> n >> q;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> d(n - 1);
  for (int i = 1; i < n - 1; i++) {
    d[i]  = d[i - 1] + (a[i] <= a[i - 1] && a[i + 1] <= a[i]);
  }

  while (q--) {
    int l, r;
    std::cin >> l >> r;
    l--, r--;
    if (l == r) {
      std::cout << 1 << "\n";
    } else {
      std::cout << (r - l + 1) - d[r - 1] + d[l] << "\n";
    }
  }

  return 0;
}