/**
 * @file    AT_dp_f LCS.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-06-18
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s, t;
  std::cin >> s >> t;

  int n = s.length(), m = t.length();
  s = '$' + s, t = '$' + t;
  std::vector f(n + 1, std::vector<int>(m + 1));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i] == t[j]) {
        f[i][j] = f[i - 1][j - 1] + 1;
      }
      f[i][j] = std::max({f[i][j], f[i - 1][j], f[i][j - 1]});
    }
  }

  std::stack<char> ans;
  int l = n, r = m;
  while (f[l][r]) {
    if (s[l] == t[r]) {
      ans.push(s[l]);
      l--, r--;
    } else {
      if (f[l][r] == f[l - 1][r]) {
        l--;
      } else {
        r--;
      }
    }
  }

  while (!ans.empty()) { std::cout << ans.top(), ans.pop(); }

  return 0;
}