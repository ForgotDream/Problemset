/**
 * @file    CF1849D Array Painting.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-07-28
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

  std::vector<int> to(n);
  std::iota(to.begin(), to.end(), 0);

  std::vector<int> pre(n), nxt(n, n - 1);
  for (int i = 0; i < n - 1; i++) {
    pre[i + 1] = a[i] == 0 ? i : pre[i];
  }
  for (int i = n - 1; i > 0; i--) {
    nxt[i - 1] = a[i] == 0 ? i : nxt[i];
  }

  for (int i = 0; i < n; i++) {
    if (a[i] == 1) {
      to[pre[i]] = std::max(to[pre[i]], i);
      to[i] = std::max(to[i], nxt[i]);
    } else if (a[i] == 2) {
      to[pre[i]] = std::max(to[pre[i]], nxt[i]);
    }
  }
  for (int i = 1; i < n; i++) {
    to[i] = std::max(to[i], to[i - 1]);
  }

  int ans = 0;
  for (int i = 0; i < n; i = to[i] + 1) {
    ans++;
  }
  std::cout << ans << "\n";

  return 0;
}