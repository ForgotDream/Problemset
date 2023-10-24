/**
 * @file    P1883 函数.cpp
 * @author  ForgotDream
 * @brief   三分
 * @date    2023-03-13
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

struct Func {
  long double a, b, c;
  Func() : a(0), b(0), c(0) {}
};

f80 calc(f80 x, std::vector<Func> a) {
  f80 res = -1e18;
  for (auto i : a) {
    res = std::max(res, i.a * x * x + i.b * x + i.c);
  }
  return res;
}

void solve() {
  static const f80 EPS = 1e-10;

  int n;
  std::cin >> n;

  std::vector<Func> a(n);
  for (auto &i : a) {
    std::cin >> i.a >> i.b >> i.c;
  }

  f80 l = 0, r = 1000;
  while (r - l > EPS) {
    f80 lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
    if (calc(lmid, a) < calc(rmid, a) + EPS) {
      r = rmid;
    } else {
      l = lmid;
    }
  }

  std::cout << std::fixed << std::setprecision(4) << calc(l, a) << "\n";

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