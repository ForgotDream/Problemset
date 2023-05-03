/**
 * @file    P1638 逛画展.cpp
 * @author  ForgotDream
 * @brief   Two Pointers
 * @date    2023-05-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    a[i]--;
  }

  int ans = n + 1, l = 0, r = 0;
  std::vector<int> cnt(m, 0);
  for (int i = 0, j = 0, num = 0; i < n; i++) {
    while (j < n && num < m) {
      if (!cnt[a[j]]) {
        num++;
      }
      cnt[a[j]]++;
      j++;
    }
    if (num == m) {
      if (ans > j - i) {
        ans = j - i;
        l = i, r = j - 1;
      }
      cnt[a[i]]--;
      if (!cnt[a[i]]) {
        num--;
      }
    }
  }

  std::cout << l + 1 << " " << r + 1 << "\n";

  return 0;
}