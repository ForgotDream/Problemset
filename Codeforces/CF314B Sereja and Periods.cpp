/**
 * @file    CF314B Sereja and Periods.cpp
 * @author  ForgotDream
 * @brief   String
 * @date    2023-08-24
 */
#include <iostream>
#include <string>

using i64 = long long;

constexpr int N = 105;
int b, d;
std::string a, c;
int nxt[N], cnt[N];
void solve() {
  std::cin >> b >> d >> a >> c;
  for (int i = 0; i < c.length(); ++i) {
    int p = i;
    for (int j = 0; j < a.length(); ++j) {
      if (a[j] == c[p]) {
        ++p;
        if (p == c.length()) cnt[i]++, p = 0;
      }
    }
    nxt[i] = p;
  }
  int p = 0;
  i64 ans = 0;
  for (int i = 1; i <= b; i++) {
    ans += cnt[p];
    p = nxt[p];
  }
  std::cout << ans / d << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  // std::cin >> t;
  while (t--) solve();
  return 0;
}