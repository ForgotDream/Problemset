/**
 * @file    CF448C Painting Fence.cpp
 * @author  ForgotDream
 * @brief   Divide and Conquer
 * @date    2023-08-29
 */
#include <algorithm>
#include <iostream>

using i64 = long long;

constexpr int N = 5050;
int n, a[N];
int solve(int l, int r) {
  if (l > r) return 0;
  if (l == r) return std::min(a[l], 1);
  int p = std::min_element(a + l, a + r + 1) - a;
  int res = a[p];
  for (int i = l; i <= r; i++) a[i] -= res;
  return std::min(res + solve(l, p - 1) + solve(p + 1, r), r - l + 1);
}
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  std::cout << std::min(solve(1, n), n) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}