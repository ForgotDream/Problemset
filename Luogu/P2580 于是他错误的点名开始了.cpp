/**
 * @file    P2580 于是他错误的点名开始了.cpp
 * @author  ForgotDream
 * @brief   字典树 or `std::map`
 * @date    2023-02-27
 */
#include <bits/stdc++.h>

using i64 = long long;

static const int N = 1e5 + 50, INF = 0x3f3f3f3f;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n;

  std::unordered_map<std::string, int> mp;
  for (int i = 1; i <= n; i++) {
    std::string s;
    std::cin >> s;
    mp.emplace(s, 0);
  }

  std::cin >> m;
  for (int i = 1; i <= m; i++) {
    std::string s;
    std::cin >> s;
    if (!mp.count(s)) {
      std::cout << "WRONG\n";
    } else if (mp[s] == 0) {
      mp[s] = 1;
      std::cout << "OK\n";
    } else {
      std::cout << "REPEAT\n";
    }
  }

  return 0;
}