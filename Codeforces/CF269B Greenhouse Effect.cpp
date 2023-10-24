/**
 * @file    CF269B Greenhouse Effect.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-15
 */
#include <bits/stdc++.h>
using i64 = long long;
using f80 = long double;
constexpr int N = 5050;
int n, m;
int a[N];
f80 b[N];
int f[N];
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i] >> b[i];
  for (int i = 1; i <= n; i++) {
    int max = 0;
    for (int j = 1; j < i; j++) {
      if (a[j] <= a[i]) max = std::max(max, f[j]);
    }
    f[i] = max + 1;
  }
  std::cout << n - *std::max_element(f + 1, f + n + 1) << "\n";
  return 0;
}