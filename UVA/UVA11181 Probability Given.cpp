/**
 * @file    UVA11181 Probability|Given.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-16
 */
#include <bits/stdc++.h>
// using i64 = long long;
// using f80 = long double;
typedef long long i64;
typedef long double f80;
// constexpr int N = 22;
const int N = 22;
int n, r, t;
f80 p[N], f[N], sum;
void solve(int t) {
  std::memset(f, 0, sizeof(f));
  sum = 0;
  for (int i = 1; i <= n; i++) std::cin >> p[i];
  int mask = (1 << n) - 1;
  for (int i = 0; i <= mask; i++) {
    if (__builtin_popcount(i) != r) continue;
    f80 cur = 1;
    for (int j = 1; j <= n; j++) {
      if (i & (1 << (j - 1))) cur *= p[j];
      else cur *= 1 - p[j];
    }
    for (int j = 1; j <= n; j++) {
      if (i & (1 << (j - 1))) f[j] += cur;
    }
    sum += cur;
  }
  std::cout << "Case " << t << ":\n";
  for (int i = 1; i <= n; i++) std::cout << f[i] / sum << "\n";
}
signed main() {
  std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  std::cin.tie(0);
  std::cout << std::fixed << std::setprecision(6);
  while (std::cin >> n >> r && (n || r)) solve(++t);
  return 0;
}