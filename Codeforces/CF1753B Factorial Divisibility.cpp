/**
 * @file    CF1753B Factorial Divisibility.cpp
 * @author  ForgotDream
 * @brief   Math
 * @date    2023-08-06
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 5e5 + 50;
int n, x, a[N], cnt[N];
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> x;
  for (int i = 1; i <= n; i++) std::cin >> a[i], cnt[a[i]]++;
  for (int i = 1; i < x; i++) {
    cnt[i + 1] += cnt[i] / (i + 1), cnt[i] %= i + 1;
  }
  for (int i = 1; i < x; i++) {
    if (cnt[i]) return std::cout << "No\n", 0;
  }
  if (cnt[x]) std::cout << "Yes\n";
  else std::cout << "No\n";
  return 0;
}