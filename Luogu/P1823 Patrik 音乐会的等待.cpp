/**
 * @file    P1823 Patrik 音乐会的等待.cpp
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

  std::stack<int> s, cnt;
  i64 ans = 0;
  for (int i = 0; i < n; i++) {
    int cur = 1;
    while (!s.empty() && a[s.top()] <= a[i]) {
      ans += cnt.top();
      if (a[i] == a[s.top()]) {
        cur += cnt.top();
      }
      s.pop(), cnt.pop();
    }
    if (!s.empty()) {
      ans++;
    }
    s.push(i), cnt.push(cur);
  }

  std::cout << ans << "\n";

  return 0;
}