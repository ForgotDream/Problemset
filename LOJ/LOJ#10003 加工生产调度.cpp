/**
 * @file    LOJ#10003 加工生产调度.cpp
 * @author  ForgotDream
 * @brief   贪心
 * @date    2023-03-17
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  for (auto &i : a) {
    std::cin >> i;
  }
  for (auto &i : b) {
    std::cin >> i;
  }

  std::vector<std::pair<int, int>> m(n);
  for (int i = 0; i < n; i++) {
    m[i].first = std::min(a[i], b[i]);
    m[i].second = i;
  }

  std::stable_sort(m.begin(), m.end());
  
  int t1 = 0, t2 = n + 1;
  std::vector<int> ans(n + 1);

  for (int i = 0; i < n; i++) {
    if (m[i].first == a[m[i].second]) {
      ans[++t1] = m[i].second;
    } else {
      ans[--t2] = m[i].second;
    }
  }

  t1 = t2 = 0;
  for (int i = 1; i <= n; i++) {
    t1 += a[ans[i]];
    if (t2 < t1) {
      t2 = t1;
    }
    t2 += b[ans[i]];
  }

  std::cout << t2 << "\n";
  for (int i = 1; i <= n; i++) {
    std::cout << ans[i] + 1 << " \n"[i == n];
  }

  return 0;
}