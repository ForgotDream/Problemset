/**
 * @file    CF1572B Xor of 3.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-08-07
 */
#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 2e5 + 50;
int t, n, a[N], s[N], ans[N];
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) s[i] = s[i - 1] ^ a[i];
  if (s[n]) return void(std::cout << "No\n");
  int idx = 0;
  for (int i = 1; i <= n; i += 2) {
    if (!s[i]) {
      idx = i;
      break;
    }
  }
  if (!idx) return void(std::cout << "NO\n");
  int cnt = 0;
  for (int i = idx - 2; i >= 1; i -= 2) ans[++cnt] = i;
  for (int i = idx + 2; i < n; i += 2) ans[++cnt] = i - 1;
  for (int i = 2; i < n; i += 2) ans[++cnt] = i - 1;
  std::cout << "YES\n" << cnt << "\n";
  for (int i = 1; i <= cnt; i++) std::cout << ans[i] << " \n"[i == cnt];
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> t;
  while (t--) solve();
  return 0;
}