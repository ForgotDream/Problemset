/**
 * @file    CF855E Salazar Slytherin's Locket.cpp
 * @author  ForgotDream
 * @brief   DP in Digits
 * @date    2023-06-09
 */
#include <bits/stdc++.h>

using i64 = long long;

i64 f[11][64][2048];

void solve() {
  int b;
  i64 l, r;
  std::cin >> b >> l >> r;

  auto calc = [&](i64 num) {
    if (num == 0) { return 1ll; }

    std::vector<int> nums;
    while (num) { nums.push_back(num % b), num /= b; }
    int cnt = nums.size() - 1;

    std::function<i64(int, int, bool, bool)> dfs =
    [&](int pos, int st, bool zero, bool isLimited) {
      if (pos == -1) { return i64(st == 0); }
      if (!isLimited && !zero && ~f[b][pos][st]) { return f[b][pos][st]; }
      i64 res = 0, up = isLimited ? nums[pos] : b - 1;
      for (int i = 0; i <= up; i++) {
        if (zero && i == 0) {
          res += dfs(pos - 1, 0, true, isLimited && i == up);
        } else {
          res += dfs(pos - 1, st ^ (1 << i), false, isLimited && i == up);
        }
      }
      if (!isLimited && !zero) { f[b][pos][st] = res; }
      return res;
    };

    return dfs(cnt, 0, true, true);
  };

  std::cout << calc(r) - calc(l - 1) << "\n";
}

signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  memset(f, -1, sizeof(f));

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}