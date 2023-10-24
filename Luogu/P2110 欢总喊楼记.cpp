/**
 * @file    P2110 欢总喊楼记.cpp
 * @author  ForgotDream
 * @brief   DP In Digits
 * @date    2023-06-09
 */
#include <bits/stdc++.h>

using i64 = long long;

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  i64 l, r;
  std::cin >> l >> r;

  i64 f[20][10];

  auto calc = [&](i64 num) {
    if (num == 0) { return 1ll; }
    std::vector<int> nums;
    while (num) { nums.push_back(num % 10), num /= 10;  }

    std::function<i64(int, int, int, bool)> dfs =
    [&](int pos, int st, int cur, bool isLimited) -> i64 {
      if (pos == -1) { return cur == st && st; }
      if (!isLimited && st && ~f[pos][st]) { return f[pos][st]; }
      i64 res = 0, up = isLimited ? nums[pos] : 9;
      for (int i = 0; i <= up; i++) {
        res += dfs(pos - 1, st ? st : i, i, isLimited && i == up);
      }
      if (!isLimited && st) { f[pos][st] = res; }
      return res;
    };

    int cnt = nums.size() - 1;
    i64 res = 0;
    for (int i = 0; i <= nums[cnt]; i++) {
      res += dfs(cnt - 1, i, i, i == nums[cnt]);
    }
    return res;
  };

  memset(f, -1, sizeof(f));
  std::cout << calc(r) - calc(l - 1) << "\n";

  return 0;
}