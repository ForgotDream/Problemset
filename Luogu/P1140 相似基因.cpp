/**
 * @file    P1140 相似基因.cpp
 * @author  ForgotDream
 * @brief   DP
 * @date    2023-05-31
 */
#include <bits/stdc++.h>

using i64 = long long;

constexpr int cost[][5] = {
  {  5, -1, -2, -1, -3 },
  { -1,  5, -3, -2, -4 },
  { -2, -3,  5, -2, -2 },
  { -1, -2, -2,  5, -1 },
  { -3, -4, -2, -1,  0 }
};

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::string s, t;
  std::cin >> n >> s >> m >> t;

  std::map<char, int> mp;
  mp['A'] = 0, mp['C'] = 1, mp['G'] = 2, mp['T'] = 3;

  std::vector f(n + 1, std::vector<int>(m + 1));
  for (int i = 1; i <= n; i++) {
    f[i][0] = f[i - 1][0] + cost[mp[s[i - 1]]][4];
  }
  for (int i = 1; i <= m; i++) {
    f[0][i] = f[0][i - 1] + cost[4][mp[t[i - 1]]];
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      f[i][j] = std::max({ 
        f[i - 1][j - 1] + cost[mp[s[i - 1]]][mp[t[j - 1]]],
        f[i - 1][j] + cost[mp[s[i - 1]]][4],
        f[i][j - 1] + cost[4][mp[t[j - 1]]],
      });
    }
  }

  std::cout << f[n][m] << "\n";

  return 0;
}