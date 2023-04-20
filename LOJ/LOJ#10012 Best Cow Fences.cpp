/**
 * @file    LOJ#10012 Best Cow Fences.cpp
 * @author  ForgotDream
 * @brief   二分
 * @date    2023-03-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  static const f80 EPS = 1e-10;

  int n, L;
  std::cin >> n >> L;

  std::vector<f80> a(n);
  for (auto &i : a) {
    std::cin >> i;
  }

  std::vector<f80> sum(n, 0);
  f80 l = -1e10, r = 1e10;
  while (r - l > EPS) {
    f80 mid = (l + r) / 2;

    // std::cerr << l << " " << r << " " << mid << "\n";

    sum[0] = a[0] - mid;
    for (int i = 1; i < n; i++) {
      sum[i] = sum[i - 1] + a[i] - mid;
    }

    f80 tmp = -1e10, minn = 1e10;
    for (int i = L - 1; i < n; i++) {
      minn = std::min(minn, i == L - 1 ? 0 : sum[i - L]);
      tmp = std::max(tmp, sum[i] - minn);
    }

    if (tmp >= 0) {
      l = mid;
    } else {
      r = mid;
    }
  }

  std::cout << int(r * 1000) << "\n";

  return 0;
}