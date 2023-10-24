/**
 * @file    P4290 玩具取名.cpp
 * @author  ForgotDream
 * @brief   Interval DP
 * @date    2023-06-02
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::map<char, int> encode;
  encode['W'] = 0, encode['I'] = 1, encode['N'] = 2, encode['G'] = 3;
  std::array<char, 4> decode = { 'W', 'I', 'N', 'G' };

  std::array<int, 4> cnt;
  for (int i = 0; i < 4; i++) {
    std::cin >> cnt[i];
  }

  std::vector rule(4, std::vector(4, std::vector<bool>(4)));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < cnt[i]; j++) {
      char u, v;
      std::cin >> u >> v;
      rule[i][encode[u]][encode[v]] = true;
    }
  }

  std::string s;
  std::cin >> s;
  int n = s.length();

  std::vector f(4, std::vector(n, std::vector<bool>(n)));
  for (int i = 0; i < n; i++) {
    f[encode[s[i]]][i][i] = true;
  }

  auto calc = [&](int l, int r, int k) {
    for (int u = 0; u < 4; u++) {
      for (int v = 0; v < 4; v++) {
        for (int w = 0; w < 4; w++) {
          if (rule[u][v][w] && f[v][l][k] && f[w][k + 1][r]) {
            f[u][l][r] = true;
          }
        }
      }
    }
  };

  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1;
      for (int k = l; k < r; k++) {
        calc(l, r, k);
      }
    }
  }

  bool flg = false;
  for (int i = 0; i < 4; i++) {
    if (f[i][0][n - 1]) {
      std::cout << decode[i];
      flg = true;
    }
  }

  if (!flg) {
    std::cout << "The name is wrong!";
  }
  std::cout << "\n";

  return 0;
}