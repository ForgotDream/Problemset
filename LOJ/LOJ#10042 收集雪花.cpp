/**
 * @file    LOJ#10042 收集雪花.cpp
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

  int n;
  std::cin >> n;

  std::vector<int> lst(n);
  std::unordered_map<int, int> mp;
  for (int i = 0; i < n; i++) {
    int cur;
    std::cin >> cur;
    if (mp.count(cur)) {
      lst[i] = mp[cur];
    } else {
      lst[i] = -1;
    }
    mp[cur] = i;
  }

  int l = 0, r = 0, ans = 1;
  while (l < n && r < n) {
    while (r < n && lst[r] < l) {
      r++;
    }
    l++;
    ans = std::max(ans, r - l + 1);
  }

  std::cout << ans << "\n";

  return 0;
}