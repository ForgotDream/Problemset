/**
 * @file    CF650B Image Preview.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-08-30
 */
#include <iostream>

using i64 = long long;

constexpr int N = 1e6 + 50;
int n, a, b, t, s;
int p[N];
char c[N];
void solve() {
  std::cin >> n >> a >> b >> t >> (c + 1);
  for (int i = 1; i <= n; i++) {
    if (c[i] == 'w')
      p[i] = p[i + n] = b + 1;
    else
      p[i] = p[i + n] = 1;
    if (i != 1) s += p[i];
  }
  int l = 2, r = n + 1, ans = 0;
  while (l <= n + 1 && r <= 2 * n) {
    s += p[r], r++;
    while (r - l > n ||
           s + a * (r - l - 1 + std::min(r - n - 2, n - l + 1)) > t) {
      s -= p[l], l++;
    }
    ans = std::max(ans, r - l);
  }
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}