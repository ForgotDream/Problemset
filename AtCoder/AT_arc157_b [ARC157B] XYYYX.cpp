/**
 * @file    AT_arc157_b [ARC157B] XYYYX.cpp
 * @author  ForgotDream
 * @brief   Ad Hoc
 * @date    2023-07-30
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::string s;
  std::cin >> n >> k >> s;

  int cnt = std::count(s.begin(), s.end(), 'Y');
  if (cnt == 0) {
    if (k > 1) std::cout << k - 1 << "\n";
    else std::cout << 0 << "\n";
    return 0;
  }

  if (k > n - cnt) {
    std::for_each(s.begin(), s.end(), [&](auto &c) {
      if (c == 'Y') c = 'X';
      else c = 'Y';
    });
    k = n - k;
  }

  cnt = std::count(s.begin(), s.end(), 'Y');
  if (cnt == 0) {
    if (k > 1) std::cout << k - 1 << "\n";
    else std::cout << 0 << "\n";
    return 0;
  }

  std::vector<int> b(n + 1);
  int lo = 0, hi;
  for (; lo < n; lo++) if (s[lo] == 'Y') break;
  for (; lo < n; lo = hi) {
    hi = lo + 1;
    while (hi < n && s[hi] == 'X') hi++;
    if (hi < n) b[hi - lo - 1]++;
  }

  int ans = 0;
  for (int i = 1; i <= n && k > 0; i++) {
    while (b[i] > 0 && k > 0) {
      if (i <= k) ans += i + 1, b[i]--, k -= i;
      else ans += k, k = 0;
    }
  }
  if (k) ans += k;
  for (int i = 1; i < n; i++) if (s[i] == 'Y' && s[i - 1] == 'Y') ans++;

  std::cout << ans << "\n";

  return 0;
}