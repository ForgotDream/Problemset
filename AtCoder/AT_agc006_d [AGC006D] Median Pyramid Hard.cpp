/**
 * @file    AT_agc006_d [AGC006D] Median Pyramid Hard.cpp
 * @author  ForgotDream
 * @brief   二分
 * @date    2023-10-10
 */
#include <iostream>

using i64 = long long;

constexpr int N = 2e5 + 50;
int n, m, a[N], b[N];
bool check(int u) {
  for (int i = 1; i <= m; i++) b[i] = a[i] >= u;
  for (int i = 0; i < n - 1; i++) {
    if (b[n + i] == b[n + i + 1]) return b[n + i];
    if (b[n - i] == b[n - i - 1]) return b[n - i];
  }
  return b[1];
}
void solve() {
  std::cin >> n;
  m = 2 * n - 1;
  for (int i = 1; i <= m; i++) std::cin >> a[i];
  int l = 1, r = m, ans = -1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) l = mid + 1, ans = mid;
    else r = mid - 1;
  }
  std::cout << ans << "\n";
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}
