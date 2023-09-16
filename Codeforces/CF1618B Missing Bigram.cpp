/**
 * @file    CF1618B Missing Bigram.cpp
 * @author  ForgotDream
 * @brief   shabi
 * @date    2023-09-08
 */
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 105;
int n;
std::string s[N], ans;
void solve() {
  std::cin >> n;
  std::string().swap(ans);
  bool flg = false;
  for (int i = 1; i <= n - 2; i++) {
    std::cin >> s[i];
    if (i != 1) {
      if (s[i - 1][1] != s[i][0]) ans += s[i][0], flg = true;
      ans += s[i][1];
    } else {
      ans = s[i];
    }
  }
  if (!flg) ans += s[n - 2][1];
  std::cout << ans << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  while (t--) solve();
  return 0;
}