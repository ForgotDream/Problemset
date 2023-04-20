/**
 * @file    LOJ#10041 门票.cpp
 * @author  ForgotDream
 * @brief   Hash
 * @date    2023-04-03
 */
#include <bits/stdc++.h>

using i64 = long long;
using i64u = unsigned long long;
using f80 = long double;

signed main() {
  #ifndef ONLINE_JUDGE
  freopen("tmp.in", "r", stdin);
  freopen("tmp.out", "w", stdout);
  #endif

  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int a, b, c;
  std::cin >> a >> b >> c;
  
  std::unordered_set<i64> s;
  i64 cur = 1;
  s.insert(1);
  for (int i = 1; i <= 2e6; i++) {
    cur = (a * cur + cur % b) % c;
    if (s.count(cur)) {
      std::cout << i << "\n";
      return 0;
    }
    s.insert(cur);
  }

  std::cout << -1 << "\n";

  return 0;
}