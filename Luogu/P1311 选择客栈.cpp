/**
 * @file    P1311 选择客栈.cpp
 * @author  ForgotDream
 * @brief   递推
 * @date    2023-05-23
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k, p;
  std::cin >> n >> k >> p;

  std::vector<int> a(n), b(n), cnt(k);
  i64 ans = 0;
  int pre = -1;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i] >> b[i];
    if (b[i] <= p) {
      for (int j = i; j > pre; j--) {
        cnt[a[j]]++;
      }
      pre = i;
      ans += cnt[a[i]] - 1;
    } else {
      ans += cnt[a[i]];
    }
  }

  std::cout << ans << "\n";

  return 0;
}