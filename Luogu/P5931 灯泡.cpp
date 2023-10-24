/**
 * @file    P5931 灯泡.cpp
 * @author  ForgotDream
 * @brief   三分
 * @date    2023-03-13
 */
#include <bits/stdc++.h>
#include <iomanip>

using i64 = long long;
using f80 = long double;

void solve() {
  static const f80 EPS = 1e-10;

  f80 H, h, D;
  std::cin >> H >> h >> D;

  auto calc = [&](f80 u) {
    return (D - u) + (H - (H - h) * D / u);
  };

  f80 l = (H - h) / H * D, r = D;
  while (r - l > EPS) {
    f80 lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
    if (calc(lmid) < calc(rmid)) {
      l = lmid;
    } else {
      r = rmid;
    }
  }

  std::cout << std::fixed << std::setprecision(3) << calc(l) << "\n";

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