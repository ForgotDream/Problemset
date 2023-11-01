/**
 * @file    CF660C Hard Process.cpp
 * @author  ForgotDream
 * @brief   Two Pointers
 * @date    2023-10-31
 */
#include <iostream>

using i64 = long long;

constexpr int N = 3e5 + 50;
int n, k, a[N];
void solve() {
  std::cin >> n >> k;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  int ans = 0, l = 0, r = 0, cnt = 0;
  for (int s = 1, t = 1; t <= n; t++) {
    cnt += !a[t];
    while (cnt > k) cnt -= !a[s++];
    if (t - s + 1 > ans) ans = t - s + 1, l = s, r = t;
  }
  for (int i = l; i <= r; i++) a[i] = 1;
  std::cout << ans << "\n";
  for (int i = 1; i <= n; i++) std::cout << a[i] << " \n"[i == n];
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
