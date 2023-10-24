/**
 * @file    P1297 [国家集训队] 单选错位.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-16
 */
#include <bits/stdc++.h>

using i64 = long long;
using f80 = long double;

constexpr int N = 1e7 + 50;
int n, A, B, C;
i64 a[N];
f80 ans;

void init() {
  for (int i = 2; i <= n; i++) a[i] = (1ll * a[i - 1] * A + B) % 100000001;
  for (int i = 1; i <= n; i++) a[i] = a[i] % C + 1;
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(3);
  
  std::cin >> n >> A >> B >> C >> a[1];
  init();

  for (int i = 2; i <= n; i++) {
    ans += 1. * std::min(a[i], a[i - 1]) / (a[i] * a[i - 1]);
  }
  ans += 1. * std::min(a[1], a[n]) / (a[1] * a[n]);
  std::cout << ans << "\n";
  
  return 0;
}